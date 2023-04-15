#include "./Components/CounterComponent.hpp"

/**
 * Constructor
 */
CounterComponent::CounterComponent() {}

/**
 * Destructor
 */
CounterComponent::~CounterComponent() {}

/**
 * Update the component. Does nothing.
 */
void CounterComponent::Update() {}

/**
 * Render the component. Does nothing.
 */
void CounterComponent::Render() {}

/**
 * @brief Set a counter
 *
 * @param name Name of the counter to set
 * @param value Value to set the counter to
 */
void CounterComponent::SetCounter(std::string name, int value) {
    m_counters[name] = value;
}

/**
 * @brief Remove a counter
 *
 * @param name Name of the counter to remove
 */
void CounterComponent::RemoveCounter(std::string name) {
    m_counters.erase(name);
}

/**
 * @brief Get a counter
 * @details If a counter with the given name does not exist, it will be created
 * and set to 0.
 * @param name Name of the counter to get
 * @return int Value of the counter
 */
int CounterComponent::GetCounter(std::string name) { return m_counters[name]; }

/**
 * @brief Increment a counter
 * @details The counter will be created and set to 0 before incrementing if it
 * does not exist.
 * @param name Name of the counter to increment
 * @param value Value to increment the counter by
 * @return int Value of the counter after incrementing
 */
int CounterComponent::IncrementCounter(std::string name, int value) {
    m_counters[name] += value;
    return m_counters[name];
}

/**
 * @brief Decrement a counter
 * @details The counter will be created and set to 0 before decrementing if it
 * @param name Name of the counter to decrement
 * @param value Value to decrement the counter by
 * @return int Value of the counter after decrementing
 */
int CounterComponent::DecrementCounter(std::string name, int value) {
    m_counters[name] -= value;
    return m_counters[name];
}