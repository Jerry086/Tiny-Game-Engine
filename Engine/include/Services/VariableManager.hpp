#pragma once
#include <string>
#include <unordered_map>

#include "IService.hpp"
class VariableManager : public IService {
    friend class ServiceLocator;

   public:
    static VariableManager &instance() {
        static VariableManager instance;
        return instance;
    }

    void ShutDown() override;
    void Update() override{};

    void SetCounter(std::string name, int value);
    int GetCounter(std::string name);
    void RemoveCounter(std::string name);
    int IncrementCounter(std::string name, int value);

    bool GetBool(std::string name);
    void SetBool(std::string name, bool value);
    bool ToggleBool(std::string name);

   private:
    std::unordered_map<std::string, int> m_counters;
    std::unordered_map<std::string, bool> m_booleans;
    VariableManager() = default;
    ~VariableManager() = default;
    VariableManager(const VariableManager &) = delete;
    VariableManager &operator=(const VariableManager &) = delete;
};