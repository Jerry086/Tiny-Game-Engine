#include "./Components/TransformComponent.hpp"

/**
 * Construct a TransformComponent with an initial position
 */
TransformComponent::TransformComponent(Vec2 position) : m_position(position) {}

/**
 * TransformComponent constructor for player given a speed, position and controller
 */
TransformComponent::TransformComponent(
    Vec2 speed, Vec2 position, std::shared_ptr<ControllerComponent> controller)
    : m_speed(speed), m_position(position), m_controller(controller) {}
/**
 * TransformComponent constructor for enemy given a speed, position and behavior
 */
TransformComponent::TransformComponent(
    Vec2 speed, Vec2 position, std::shared_ptr<BehaviorComponent> behavior)
    : m_speed(speed), m_position(position), m_behavior(behavior) {}
/**
 * Destructor
 */
TransformComponent::~TransformComponent() {}
/**
 * Update the position of a game object if the game object is dynamic
 */
void TransformComponent::Update()
{
    if (m_behavior != nullptr)
    {
        m_position.x += m_behavior->GetDirectionX() * m_speed.x;
        m_position.y += m_behavior->GetDirectionY() * m_speed.y;
    }
    else if (m_controller != nullptr)
    {
        m_position.x += m_controller->GetDirectionX() * m_speed.x;
        m_position.y += m_controller->GetDirectionY() * m_speed.y;
    }
}
