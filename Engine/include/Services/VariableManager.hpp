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

    static void SetCounter(std::string name, int value);
    static int GetCounter(std::string name);
    static void RemoveCounter(std::string name);
    static int IncrementCounter(std::string name, int value);
    static void ResetAllCounters();

    static bool GetBool(std::string name);
    static void SetBool(std::string name, bool value);
    static bool ToggleBool(std::string name);
    static void ResetAllBools();

   private:
    std::unordered_map<std::string, int> m_counters;
    std::unordered_map<std::string, bool> m_booleans;
    VariableManager() = default;
    // ~VariableManager() = default;
    VariableManager(const VariableManager &) = delete;
    VariableManager &operator=(const VariableManager &) = delete;
};