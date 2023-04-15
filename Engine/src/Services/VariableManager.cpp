#include "./Services/VariableManager.hpp"

#include <iostream>

void VariableManager::ShutDown() {
    m_counters.clear();
    m_booleans.clear();
}

void VariableManager::SetCounter(std::string name, int value) {
    m_counters[name] = value;
    std::cout << "Set counter " << name << " to " << value << std::endl;
}

int VariableManager::GetCounter(std::string name) { return m_counters[name]; }

void VariableManager::RemoveCounter(std::string name) {
    m_counters.erase(name);
}

int VariableManager::IncrementCounter(std::string name, int value) {
    m_counters[name] += value;
    std::cout << "Incremented counter " << name << " by " << value << std::endl;
    return m_counters[name];
}

bool VariableManager::GetBool(std::string name) { return m_booleans[name]; }

void VariableManager::SetBool(std::string name, bool value) {
    m_booleans[name] = value;
    std::cout << "Set bool " << name << " to " << value << std::endl;
}

bool VariableManager::ToggleBool(std::string name) {
    m_booleans[name] = !m_booleans[name];
    std::cout << "Toggled bool " << name << " to " << m_booleans[name]
              << std::endl;
    return m_booleans[name];
}