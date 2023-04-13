#include "./Components/BehaviorComponent.hpp"

/**
 * Constructor
 */
BehaviorComponent::BehaviorComponent() {}
/**
 * Destructor
 */
BehaviorComponent::~BehaviorComponent() {}
/**
 * Update the moving direction of the game object
 * Flip the moving directions after a certain amount of frames
 */
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

/**
 * Getter of current moving direction towards x-axis
 */
int BehaviorComponent::GetDirectionX()
{
    return m_direction_x;
}
/**
 * Getter of current moving direction towards y-axis
 */
int BehaviorComponent::GetDirectionY()
{
    return m_direction_y;
}
/**
 * Getter of the component type
 */
int BehaviorComponent::GetType()
{
    return m_type;
}