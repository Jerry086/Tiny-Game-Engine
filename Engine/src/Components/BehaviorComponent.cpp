#include "./Components/BehaviorComponent.hpp"

#include "Vec.hpp"

// Construct a transform component with an initial position (x, y)
BehaviorComponent::BehaviorComponent()
{
}

BehaviorComponent::~BehaviorComponent() {}

void BehaviorComponent::Update()
{
    ++counter_x;
    ++counter_y;
    if (counter_x > 150)
    {
        m_direction_x = -m_direction_x;
        counter_x = 0;
    }
    if (counter_y > 100)
    {
        m_direction_y = -m_direction_y;
        counter_y = 0;
    }
}

// Getter of current moving direction
int BehaviorComponent::GetDirectionX()
{
    return m_direction_x;
}

int BehaviorComponent::GetDirectionY()
{
    return m_direction_y;
}
