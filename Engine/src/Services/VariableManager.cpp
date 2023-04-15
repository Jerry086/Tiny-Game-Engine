#include "./Services/VariableManager.hpp"

void VariableManager::ShutDown() {
    m_counters.clear();
    m_booleans.clear();
}

void VariableManager::SetCounter(std::string name, int value) {
    m_counters[name] = value;
}

int VariableManager::GetCounter(std::string name) { return m_counters[name]; }

void VariableManager::RemoveCounter(std::string name) {
    m_counters.erase(name);
}

int VariableManager::IncrementCounter(std::string name, int value) {
    m_counters[name] += value;
    return m_counters[name];
}

bool VariableManager::GetBool(std::string name) { return m_booleans[name]; }

void VariableManager::SetBool(std::string name, bool value) {
    m_booleans[name] = value;
}

bool VariableManager::ToggleBool(std::string name) {
    m_booleans[name] = !m_booleans[name];
    return m_booleans[name];
}