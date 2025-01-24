#include "Factory.h"

Factory::~Factory() {
    for (auto& [key, value] : m_registry) {
        delete value;
    }
    m_registry.clear();
}

void Factory::registerType(const std::string& key, ICommand* command) {
    m_registry[key] = command;
}

ICommand* Factory::create(const std::string& key, std::string& output, void* context) {
    if (m_registry.find(key) != m_registry.end()) {
        return m_registry[key]->clone();
    }
    return nullptr;
}