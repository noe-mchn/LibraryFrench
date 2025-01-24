#ifndef INTERPRETERBUILDER_H
#define INTERPRETERBUILDER_H

#include "Factory.h"
#include "ICommand.h"
#include "EchoCommand.h"
#include <queue>
#include <string>

class InterpreterBuilder {
public:
    InterpreterBuilder();

    void addCommand(const std::string& input, std::string& outputMsg, void* context);
    void executeAndPopCommand();
    void executeCommand(const std::string& input);

private:
    Factory m_factory;
    std::queue<ICommand*> m_commandQueue;
};

#endif // INTERPRETERBUILDER_H
