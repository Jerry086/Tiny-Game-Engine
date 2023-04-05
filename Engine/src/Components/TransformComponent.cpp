#include "./Components/TransformComponent.hpp"

#include "Vec.hpp"

// Construct a transform component with an initial position (x, y)
TransformComponent::TransformComponent(Vec2 new_position)
{
    m_position.x = new_position.x;
    m_position.y = new_position.y;
}

// Construct a transform component with an initial position (x, y)
TransformComponent::TransformComponent(Vec2 speed, Vec2 new_position,
                                       std::shared_ptr<ControllerComponent> controller)
    : m_controller(controller)
{
    m_position.x = new_position.x;
    m_position.y = new_position.y;
    m_speed.x = speed.x;
    m_speed.y = speed.y;
}

// Construct a transform component with an initial position (x, y)
TransformComponent::TransformComponent(Vec2 speed, Vec2 new_position,
                                       std::shared_ptr<BehaviorComponent> controller)
    : behavior_controller(controller)
{
    m_position.x = new_position.x;
    m_position.y = new_position.y;
    m_speed.x = speed.x;
    m_speed.y = speed.y;
}

TransformComponent::~TransformComponent() {}

void TransformComponent::Update()
{
    if (m_controller == nullptr && behavior_controller != nullptr){
        m_position.x += behavior_controller->GetDirectionX() * m_speed.x;
        m_position.y += behavior_controller->GetDirectionY() * m_speed.y;
    }else if(m_controller != nullptr && behavior_controller == nullptr){
        m_position.x += m_controller->GetDirectionX() * m_speed.x;
        m_position.y += m_controller->GetDirectionY() * m_speed.y;
    }else{
        return;
    }

    // std::cout << "x: " << m_position.x << " direction: " << m_controller->GetDirectionX() << " direction x: " << m_direction.x << std::endl;

}
