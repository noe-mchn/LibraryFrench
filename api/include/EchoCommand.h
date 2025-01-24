#ifndef ECHOCOMMAND_H
#define ECHOCOMMAND_H

#include "ICommand.h"
#include <string>

class EchoCommand : public ICommand {
public:
    static const std::string name;
    EchoCommand(const std::string& outputmessage);

    void apply() override;
    ICommand* clone() const override; 

private:
    std::string outputmessage;
};

#endif // ECHOCOMMAND_H