#ifndef FACTORY_H
#define FACTORY_H

#include "ICommand.h"
#include <string>
#include <map>

class Factory {
public:
    void registerType(const std::string& key, ICommand* command);
    ICommand* create(const std::string& key, std::string& output, void* context);
    ~Factory();

private:
    std::map<std::string, ICommand*> m_registry;
};

#endif // FACTORY_H