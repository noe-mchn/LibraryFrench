#include "ConsoleFramebuffer.h"
#include <stdexcept>
#include <conio.h>

class ConsoleFramebufferPrivateImpl {
public:
    ConsoleFramebufferPrivateImpl();
    ~ConsoleFramebufferPrivateImpl();

    void initialize();
    void clear(const std::string& lastCommand);
    void print(const std::string& text, Color color);
    void println(const std::string& text, Color color);
    std::string readLine();
    void show();
    void setString(const std::string& text, Color color = Color::White, Color backColor = Color::Black);
    std::string getLastCommand();
    void writeConsole();

private:
    WORD convertColorToWindows(Color foreground, Color background);
    HANDLE m_handleoutput;
    HANDLE m_handleinput;
    std::vector<std::string> m_commandHistory;
    size_t m_historyIndex;
    std::string m_lastCommand;
};

ConsoleFramebufferPrivateImpl::ConsoleFramebufferPrivateImpl()
    : m_handleoutput(GetStdHandle(STD_OUTPUT_HANDLE)),
    m_handleinput(GetStdHandle(STD_INPUT_HANDLE)),
    m_historyIndex(0) {}

ConsoleFramebufferPrivateImpl::~ConsoleFramebufferPrivateImpl() {}

void ConsoleFramebufferPrivateImpl::initialize() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

WORD ConsoleFramebufferPrivateImpl::convertColorToWindows(Color foreground, Color background) {
    WORD foregroundAttr = 0;
    WORD backgroundAttr = 0;

    switch (foreground) {
    case Color::Black:
        foregroundAttr = 0;
        break;
    case Color::Red:
        foregroundAttr = FOREGROUND_RED | FOREGROUND_INTENSITY;
        break;
    case Color::Green:
        foregroundAttr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        break;
    case Color::Blue:
        foregroundAttr = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;
    case Color::White:
        foregroundAttr = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        break;
    case Color::Orange:
        foregroundAttr = FOREGROUND_RED | FOREGROUND_GREEN;
        break;
    default:
        foregroundAttr = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }

    switch (background) {
    case Color::Black:
        backgroundAttr = 0;
        break;
    case Color::Red:
        backgroundAttr = BACKGROUND_RED | BACKGROUND_INTENSITY;
        break;
    case Color::Green:
        backgroundAttr = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        break;
    case Color::Blue:
        backgroundAttr = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
        break;
    case Color::White:
        backgroundAttr = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
        break;
    case Color::Orange:
        backgroundAttr = BACKGROUND_RED | BACKGROUND_GREEN;
        break;
    default:
        backgroundAttr = 0;
    }

    return foregroundAttr | backgroundAttr;
}

void ConsoleFramebufferPrivateImpl::clear(const std::string& lastCommand) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void ConsoleFramebufferPrivateImpl::print(const std::string& text, Color color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE)
        throw std::runtime_error("Cannot get console handle");

    WORD attributes = convertColorToWindows(color, Color::Black);

    SetConsoleTextAttribute(hConsole, attributes);

    DWORD written = 0;
    WriteConsole(hConsole, text.c_str(), text.size(), &written, nullptr);

    SetConsoleTextAttribute(hConsole, convertColorToWindows(Color::White, Color::Black));
}

void ConsoleFramebufferPrivateImpl::println(const std::string& text, Color color) {
    print(text + "\n", color);
}

std::string ConsoleFramebufferPrivateImpl::readLine() {
    std::string input;
    int cursorPos = 0;

    while (true) {
        if (_kbhit()) {
            int ch = _getch();

            if (ch == '\r' || ch == '\n') {
                println("", Color::Blue);
                if (!input.empty()) {
                    m_commandHistory.push_back(input);
                    m_historyIndex = m_commandHistory.size();
                }
                return input;
            }
            else if (ch == '\b' && cursorPos > 0) {
                input.erase(--cursorPos, 1);
                print("\b \b", Color::White);
            }
            else if (ch == 224) {
                int specialKey = _getch();
                if (specialKey == 72 && !m_commandHistory.empty()) {
                    if (m_historyIndex > 0) {
                        --m_historyIndex;
                        while (cursorPos > 0) {
                            print("\b \b", Color::White);
                            --cursorPos;
                        }
                        input = m_commandHistory[m_historyIndex];
                        print(input, Color::White);
                        cursorPos = input.length();
                    }
                }
                else if (specialKey == 80 && !m_commandHistory.empty()) {
                    if (m_historyIndex < m_commandHistory.size()) {
                        m_historyIndex++;
                        while (cursorPos > 0) {
                            print("\b \b", Color::White);
                            --cursorPos;
                        }
                        if (m_historyIndex < m_commandHistory.size())
                            input = m_commandHistory[m_historyIndex];
                        else
                            input.clear();

                        print(input, Color::White);
                        cursorPos = input.length();
                    }
                }
            }
            else if (ch >= 32 && ch <= 126) { 
                input.insert(cursorPos++, 1, static_cast<char>(ch));
                print(std::string(1, static_cast<char>(ch)), Color::Red);
            }
        }
    }
}

void ConsoleFramebufferPrivateImpl::show() {
}

void ConsoleFramebufferPrivateImpl::setString(const std::string& text, Color color, Color backColor) {
}

std::string ConsoleFramebufferPrivateImpl::getLastCommand() {
    return m_lastCommand;
}

void ConsoleFramebufferPrivateImpl::writeConsole() {
    m_lastCommand = readLine();
}

ConsoleFramebuffer::ConsoleFramebuffer()
    : m_impl(new ConsoleFramebufferPrivateImpl()) {}

ConsoleFramebuffer::~ConsoleFramebuffer() {
    delete m_impl;
}

void ConsoleFramebuffer::initialize() {
    m_impl->initialize();
}

void ConsoleFramebuffer::clear(const std::string& lastCommand) {
    m_impl->clear(lastCommand);
}

void ConsoleFramebuffer::print(const std::string& text, Color color) {
    m_impl->print(text, color);
}

void ConsoleFramebuffer::println(const std::string& text, Color color) {
    m_impl->println(text, color);
}

std::string ConsoleFramebuffer::readLine() {
    return m_impl->readLine();
}

void ConsoleFramebuffer::show() {
    m_impl->show();
}

void ConsoleFramebuffer::setString(const std::string& text, Color color, Color backColor) {
    m_impl->setString(text, color, backColor);
}

std::string ConsoleFramebuffer::getLastCommand() {
    return m_impl->getLastCommand();
}

void ConsoleFramebuffer::writeConsole() {
    m_impl->writeConsole();
}