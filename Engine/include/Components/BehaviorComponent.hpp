#ifndef BEHAVIORCOMPONENT_HPP
#define BEHAVIORCOMPONENT_HPP

#include <memory>

#include "Component.hpp"
#include "Vec.hpp"

// Directions of movement
class BehaviorComponent : public Component
{
public:
    // Constructor
    BehaviorComponent();
    // Destructor
    ~BehaviorComponent();
    // Update position of a game object
    void Update() override;

    int GetDirectionX();
    int GetDirectionY();

private:
    int m_direction_x = -1;
    int m_direction_y = 1;
    int counter_x = 0;
    int counter_y = 0;
};

#endif
