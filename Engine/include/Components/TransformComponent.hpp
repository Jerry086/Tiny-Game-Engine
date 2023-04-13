#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <memory>

#include "Component.hpp"
#include "ControllerComponent.hpp"
#include "BehaviorComponent.hpp"
#include "Vec.hpp"

/**
 * The TransformComponent class that defines the position of a game object.
 */
class TransformComponent : public Component
{
public:
    /**
     * Constructor
     * @param position The initial position of a game object
     */
    TransformComponent(Vec2 position);
    /**
     * Constructor
     * @param speed The speed of a game object
     * @param position The initial position of a game object
     * @param controller The controller of a game object
     */
    TransformComponent(Vec2 direction, Vec2 position,
                       std::shared_ptr<ControllerComponent> controller);
    /**
     * Constructor
     * @param speed The speed of a game object
     * @param position The initial position of a game object
     * @param behavior The behavior of a game object
     */
    TransformComponent(Vec2 direction, Vec2 position,
                       std::shared_ptr<BehaviorComponent> behavior);
    /**
     * Destructor
     */
    ~TransformComponent();
    /**
     * Update the position of a game object
     */
    void Update() override;
    /**
     * Getter of the component type
     * @return The type of the component
     */
    int GetType() override;

    Vec2 m_position;
    Vec2 m_speed;
    std::shared_ptr<ControllerComponent> m_controller = nullptr;
    std::shared_ptr<BehaviorComponent> m_behavior = nullptr;

private:
    const int m_type = TransformComponent_TYPE;
};

#endif
