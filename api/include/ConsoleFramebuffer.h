#ifndef CONSOLEFRAMEBUFFER_H
#define CONSOLEFRAMEBUFFER_H

#include <windows.h>
#include <string>
#include <vector>

enum class Color {
    Black,
    Red,
    Green,
    Blue,
    White,
    Orange
};

class ConsoleFramebufferPrivateImpl;

class ConsoleFramebuffer {
public:
    ConsoleFramebuffer();
    ~ConsoleFramebuffer();

    void initialize();
    void clear(const std::string& lastCommand);
    void print(const std::string& text, Color color = Color::White);
    void println(const std::string& text, Color color = Color::White);
    std::string readLine();
    void show();
    void setString(const std::string& text, Color color = Color::White, Color backColor = Color::Black);
    std::string getLastCommand();
    void writeConsole();

private:
    ConsoleFramebufferPrivateImpl* m_impl;
};

#endif // CONSOLEFRAMEBUFFER_H