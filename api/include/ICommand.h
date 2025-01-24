#ifndef ICOMMAND_H
#define ICOMMAND_H

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void apply() = 0;
    virtual ICommand* clone() const = 0;
};

#endif // ICOMMAND_H