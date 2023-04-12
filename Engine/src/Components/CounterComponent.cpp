#include "./Components/CounterComponent.hpp"

CounterComponent::CounterComponent() {}

CounterComponent::~CounterComponent() {}

void CounterComponent::Update() {}

void CounterComponent::Render() {}

void CounterComponent::SetCounter(std::string name, int value) {
    m_counters[name] = value;
}

void CounterComponent::RemoveCounter(std::string name) {
    m_counters.erase(name);
}

int CounterComponent::GetCounter(std::string name) { return m_counters[name]; }
