#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <memory>

#include "Component.hpp"
#include "ControllerComponent.hpp"
#include "BehaviorComponent.hpp"
#include "Vec.hpp"

class TransformComponent : public Component
{
public:
    // Position of a game object
    Vec2 m_position;
    Vec2 m_speed;
    // Constructor
    TransformComponent(Vec2 position);
    TransformComponent(Vec2 direction, Vec2 position,
                       std::shared_ptr<ControllerComponent> controller);
    TransformComponent(Vec2 direction, Vec2 position,
                       std::shared_ptr<BehaviorComponent> behavior);
    // Destructor
    ~TransformComponent();
    // Update position of a game object
    void Update() override;

    std::shared_ptr<ControllerComponent> m_controller = nullptr;
    std::shared_ptr<BehaviorComponent> m_behavior = nullptr;

private:
};

#endif
