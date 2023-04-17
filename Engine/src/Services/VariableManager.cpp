#include "./Services/VariableManager.hpp"

#include <iostream>

void VariableManager::ShutDown() {
    m_counters.clear();
    m_booleans.clear();
}

void VariableManager::SetCounter(std::string name, int value) {
    VariableManager::instance().m_counters[name] = value;
}

int VariableManager::GetCounter(std::string name) {
    return VariableManager::instance().m_counters[name];
}

void VariableManager::RemoveCounter(std::string name) {
    VariableManager::instance().m_counters.erase(name);
}

int VariableManager::IncrementCounter(std::string name, int value) {
    VariableManager::instance().m_counters[name] += value;
    return VariableManager::instance().m_counters[name];
}

bool VariableManager::GetBool(std::string name) {
    return VariableManager::instance().m_booleans[name];
}

void VariableManager::SetBool(std::string name, bool value) {
    VariableManager::instance().m_booleans[name] = value;
}

bool VariableManager::ToggleBool(std::string name) {
    VariableManager::instance().m_booleans[name] =
        !VariableManager::instance().m_booleans[name];
    return VariableManager::instance().m_booleans[name];
}

void VariableManager::ResetAllCounters() {
    VariableManager::instance().m_counters.clear();
}

void VariableManager::ResetAllBools() {
    VariableManager::instance().m_booleans.clear();
}

std::string VariableManager::GetDict(std::string name) {
    return VariableManager::instance().m_dict[name];
}

void VariableManager::SetDict(std::string name, std::string value) {
    VariableManager::instance().m_dict[name] = value;
}