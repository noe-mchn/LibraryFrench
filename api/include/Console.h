#ifndef CONSOLE_H
#define CONSOLE_H

#include "LibraryManager.h"
#include "ConsoleFramebuffer.h"
#include <string>
#include <map>
#include <vector>
#include <functional>

class Console {
public:
    Console();
    void run();
    void parseCommand(const std::string& input, std::string& outputMsg);
    void listCommands(std::string& outputMsg);

private:
    void registerCommands();
    LibraryManager manager;
    ConsoleFramebuffer consoleFramebuffer;
    std::map<std::string, std::function<void(const std::vector<std::string>&, std::string&)>> commands;
    std::map<std::string, std::string> commandDescriptions;
};

#endif // CONSOLE_H