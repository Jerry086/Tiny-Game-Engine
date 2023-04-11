#ifndef COUNTERCOMPONENT_HPP
#define COUNTERCOMPONENT_HPP

#include <unordered_map>

#include "Component.hpp"

class CounterComponent : public Component {
   public:
    CounterComponent();
    ~CounterComponent();
    void Update();
    void Render();

    int GetCounter(std::string name);
    void SetCounter(std::string name, int value);
    void RemoveCounter(std::string name);

   private:
    std::unordered_map<std::string, int> m_counters;
};

#endif