#include "./Components/TransformComponent.hpp"

#include "Vec.hpp"

// Construct a transform component with an initial position (x, y)
TransformComponent::TransformComponent(Vec2 direction, Vec2 new_position,
                                       ControllerComponent &controller)
    : m_controller(controller) {
    m_position.x = new_position.x;
    m_position.y = new_position.y;
    m_direction.x = direction.x;
    m_direction.y = direction.y;
}

TransformComponent::~TransformComponent() {}

void TransformComponent::Update() {
    m_position.x += m_controller.GetDirectionX() * m_direction.x;
    m_position.y += m_controller.GetDirectionY() * m_direction.y;
}
