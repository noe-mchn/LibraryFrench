#include "InterpreterBuilder.h"
#include <sstream>
#include <iomanip>

InterpreterBuilder::InterpreterBuilder() {
    m_factory.registerType(EchoCommand::name, new EchoCommand(""));
}

std::vector<std::string> parseArguments(const std::string& input) {
    std::istringstream stream(input);
    std::vector<std::string> args;
    std::string arg;

    while (stream >> std::quoted(arg)) {
        args.push_back(arg);
    }
    return args;
}

void InterpreterBuilder::addCommand(const std::string& input, std::string& outputMsg, void* context) {
    auto args = parseArguments(input);
    if (args.empty()) return;

    auto* command = m_factory.create(args[0], outputMsg, context);
    if (command) {
        m_commandQueue.push(command);
    }
}

void InterpreterBuilder::executeAndPopCommand() {
    if (!m_commandQueue.empty()) {
        auto* command = m_commandQueue.front();
        command->apply();
        delete command;
        m_commandQueue.pop();
    }
}

void InterpreterBuilder::executeCommand(const std::string& input) {
    std::string outputMsg;
    addCommand(input, outputMsg, nullptr);
    executeAndPopCommand();
}