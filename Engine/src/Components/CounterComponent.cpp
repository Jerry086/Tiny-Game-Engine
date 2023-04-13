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
 *
 * @param name Name of the counter to get
 * @return int Value of the counter
 */
int CounterComponent::GetCounter(std::string name) { return m_counters[name]; }
