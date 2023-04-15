#ifndef COUNTERCOMPONENT_HPP
#define COUNTERCOMPONENT_HPP

#include <unordered_map>

#include "Component.hpp"

/*
 * @brief The CounterComponent class
 *
 * A component that keeps track of counters
 */
class CounterComponent : public Component {
   public:
    CounterComponent();
    ~CounterComponent();
    void Update();
    void Render();

    int GetCounter(std::string name);
    void SetCounter(std::string name, int value);
    void RemoveCounter(std::string name);
    int IncrementCounter(std::string name, int value);
    int DecrementCounter(std::string name, int value);

   private:
    std::unordered_map<std::string, int> m_counters;
};

#endif