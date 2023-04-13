#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include "Component.hpp"
#include "ControllerComponent.hpp"
#include "TransformComponent.hpp"
#include "GameObjectManager.hpp"

/**
 * @brief The type of the collision component
 */
enum ObjectType
{
    player,
    wall,
    enemy,
    interactable
};

/**
 * @brief The CollisionComponent class
 *
 * A component that handles collision
 */
class CollisionComponent : public Component
{
public:
    /**
     * @brief Constructor
     * @param objectType The type of the object
     * @param transformer The transform component of the object
     * @param w The width of the object
     * @param h The height of the object
     */
    CollisionComponent(std::string objectType, std::shared_ptr<TransformComponent> transformer, int w, int h);
    /**
     * @brief Destructor
     */
    ~CollisionComponent();
    /**
     * @brief Check collision with another object
     * @param other The other object
     * @return The penetration vector
     */
    Vec2 CheckCollision(std::shared_ptr<CollisionComponent> other);
    /**
     * @brief Update the component
     */
    void Update() override;
    /**
     * @brief Getter of the component type
     * @return The type of the component
     */
    int GetType() override;
    /**
     * @brief Getter of the object type
     * @return The type of the object
     */
    ObjectType GetObjectType();

    std::shared_ptr<TransformComponent> m_transformer;

private:
    int m_height;
    int m_width;
    const int m_type = CollisionComponent_TYPE;
    std::string m_objectType;
    ObjectType m_objectType_enum;
    std::shared_ptr<ControllerComponent> m_controller = nullptr;
    std::shared_ptr<BehaviorComponent> m_behavior = nullptr;
};

#endif
