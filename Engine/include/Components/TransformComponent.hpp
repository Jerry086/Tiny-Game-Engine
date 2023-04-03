#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Vec.hpp"
#include "Component.hpp"
#include "ControllerComponent.hpp"

class TransformComponent : public Component
{
public:
    // Position of a game object
    Vec2 m_position;
    Vec2 m_direction;
    // Constructor
    TransformComponent(Vec2 direction, Vec2 new_position, std::shared_ptr<ControllerComponent> controller);
    // Destructor
    ~TransformComponent();
    // Update position of a game object
    void Update() override;

private:
    std::shared_ptr<ControllerComponent> m_controller;
};

#endif
