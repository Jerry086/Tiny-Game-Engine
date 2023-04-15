#include "./Services/VariableManager.hpp"

#include <iostream>

void VariableManager::ShutDown() {
    m_counters.clear();
    m_booleans.clear();
}

void VariableManager::SetCounter(std::string name, int value) {
    VariableManager::instance().m_counters[name] = value;
    std::cout << "Set counter " << name << " to " << value << std::endl;
}

int VariableManager::GetCounter(std::string name) {
    return VariableManager::instance().m_counters[name];
}

void VariableManager::RemoveCounter(std::string name) {
    VariableManager::instance().m_counters.erase(name);
}

int VariableManager::IncrementCounter(std::string name, int value) {
    VariableManager::instance().m_counters[name] += value;
    std::cout << "Incremented counter " << name << " by " << value << std::endl;
    return VariableManager::instance().m_counters[name];
}

bool VariableManager::GetBool(std::string name) {
    return VariableManager::instance().m_booleans[name];
}

void VariableManager::SetBool(std::string name, bool value) {
    VariableManager::instance().m_booleans[name] = value;
    std::cout << "Set bool " << name << " to " << value << std::endl;
}

bool VariableManager::ToggleBool(std::string name) {
    VariableManager::instance().m_booleans[name] =
        !VariableManager::instance().m_booleans[name];
    std::cout << "Toggled bool " << name << " to "
              << VariableManager::instance().m_booleans[name] << std::endl;
    return VariableManager::instance().m_booleans[name];
}

void VariableManager::ResetAllCounters() {
    VariableManager::instance().m_counters.clear();
}

void VariableManager::ResetAllBools() {
    VariableManager::instance().m_booleans.clear();
}