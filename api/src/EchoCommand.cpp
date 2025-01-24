#include "EchoCommand.h"
#include <iostream>

const std::string EchoCommand::name = "echo";

EchoCommand::EchoCommand(const std::string& outputmessage) : outputmessage(outputmessage) {}

void EchoCommand::apply() {
    std::cout << outputmessage << std::endl;
}

ICommand* EchoCommand::clone() const {
    return new EchoCommand(*this); 
}