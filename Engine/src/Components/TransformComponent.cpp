#include "./Components/TransformComponent.hpp"

// Construct a transform component with an initial position (x, y)
TransformComponent::TransformComponent(Vec2 position) : m_position(position) {
    std::cout << "TransformComponent created, position " << m_position.x << ", "
              << m_position.y << std::endl;
}

// Transformer for player
TransformComponent::TransformComponent(
    Vec2 speed, Vec2 position, std::shared_ptr<ControllerComponent> controller)
    : m_speed(speed), m_position(position), m_controller(controller) {
    std::cout << "TransformComponent created, position " << m_position.x << ", "
              << m_position.y << " speed " << m_speed.x << ", " << m_speed.y
              << " with controller " << m_controller << std::endl;
}

// Transformer for enemies
TransformComponent::TransformComponent(
    Vec2 speed, Vec2 position, std::shared_ptr<BehaviorComponent> behavior)
    : m_speed(speed), m_position(position), m_behavior(behavior) {
    std::cout << "TransformComponent created, position " << m_position.x << ", "
              << m_position.y << " speed " << m_speed.x << ", " << m_speed.y
              << " with behavior " << m_behavior << std::endl;
}

TransformComponent::~TransformComponent() {}

void TransformComponent::Update() {
    if (m_behavior) {
        m_position.x += m_behavior->GetDirectionX() * m_speed.x;
        m_position.y += m_behavior->GetDirectionY() * m_speed.y;
    } else if (m_controller) {
        m_position.x += m_controller->GetDirectionX() * m_speed.x;
        m_position.y += m_controller->GetDirectionY() * m_speed.y;
    }
}
