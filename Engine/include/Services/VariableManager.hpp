#pragma once
#include <string>
#include <unordered_map>

#include "IService.hpp"

/**
 * @brief Class to manage "global" variables
 *
 */
class VariableManager : public IService {
    friend class ServiceLocator;

   public:
    /**
     * @brief Shutdown the VariableManager
     *
     */
    void ShutDown() override;

    /**
     * @brief Set the Counter object
     *
     * @param name counter name
     * @param value value to set
     */
    static void SetCounter(std::string name, int value);

    /**
     * @brief Get the value of a counter
     *
     * @param name counter name
     * @return int counter value
     */
    static int GetCounter(std::string name);

    /**
     * @brief Remove a counter by name
     * @param name counter name
     */
    static void RemoveCounter(std::string name);

    /**
     * @brief Increment a counter by a value
     * @details increment value can be negative (so it can be used to decrement)
     * @param name counter name
     * @param value value to increment by
     * @return int new counter value
     */
    static int IncrementCounter(std::string name, int value);

    /**
     * @brief Reset all counters
     *
     */
    static void ResetAllCounters();

    /**
     * @brief Get a boolean by name
     *
     * @param name boolean name
     * @return true
     * @return false
     */
    static bool GetBool(std::string name);

    /**
     * @brief Set a boolean by name
     *
     * @param name boolean name
     * @param value value to set to
     */
    static void SetBool(std::string name, bool value);

    /**
     * @brief Toggle a boolean by name
     *
     * @param name boolean name
     * @return true
     * @return false
     */
    static bool ToggleBool(std::string name);

    /**
     * @brief Reset all booleans
     *
     */
    static void ResetAllBools();

    /**
     * @brief Get a string variable by name
     *
     * @param name string name to get
     * @return std::string value of the string
     */
    static std::string GetDict(std::string name);

    /**
     * @brief Set a string variable by name
     *
     * @param name string name to set
     * @param value value to set to
     */
    static void SetDict(std::string name, std::string value);

   private:
    std::unordered_map<std::string, int> m_counters;
    std::unordered_map<std::string, bool> m_booleans;
    std::unordered_map<std::string, std::string> m_dict;
    VariableManager() = default;
    // ~VariableManager() = default;
    VariableManager(const VariableManager &) = delete;
    VariableManager &operator=(const VariableManager &) = delete;

    static VariableManager &instance() {
        static VariableManager instance;
        return instance;
    }
};