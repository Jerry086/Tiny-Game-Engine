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
    TransformComponent(Vec2 new_position);
    TransformComponent(Vec2 direction, Vec2 new_position,
                       std::shared_ptr<ControllerComponent> controller);
    TransformComponent(Vec2 direction, Vec2 new_position,
                        std::shared_ptr<BehaviorComponent> controller);
    // Destructor
    ~TransformComponent();
    // Update position of a game object
    void Update() override;
    std::shared_ptr<ControllerComponent> m_controller = nullptr;
    std::shared_ptr<BehaviorComponent> behavior_controller = nullptr;

private:

};

#endif
