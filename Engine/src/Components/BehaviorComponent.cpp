#include "./Components/BehaviorComponent.hpp"

#include "Vec.hpp"

// Construct a transform component with an initial position (x, y)
BehaviorComponent::BehaviorComponent()
{
}

BehaviorComponent::~BehaviorComponent() {}

void BehaviorComponent::Update()
{
    std::cout << "counter " << counter <<std::endl;
    counter++;
    if(counter > 150){
            std::cout << "m_direction_x " << m_direction_x <<std::endl;
        m_direction_x = -m_direction_x;
        counter = 0;
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
