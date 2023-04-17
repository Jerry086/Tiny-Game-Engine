#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "./Services/GameObjectManager.hpp"
#include "Component.hpp"
#include "ControllerComponent.hpp"
#include "TransformComponent.hpp"

/**
 * @brief The type of the collision component
 */
enum ObjectType { player = 1, wall = 2, enemy = 3, interactable = 4, none = 0 };

/**
 * @brief The CollisionComponent class
 *
 * A component that handles collision
 */
class CollisionComponent : public Component {
   public:
    /**
     * @brief Constructor
     * @param objectType The type of the object
     * @param transformer The transform component of the object
     * @param w The width of the object
     * @param h The height of the object
     */
    CollisionComponent(std::string objectType,
                       std::shared_ptr<TransformComponent> transform, int w,
                       int h);

    CollisionComponent(std::string objectType,
                       std::shared_ptr<TransformComponent> transform, int w,
                       int h, std::unordered_map<std::string, int> counters_set,
                       std::unordered_map<std::string, int> counters_increment,
                       std::vector<std::string> bools_true,
                       std::vector<std::string> bools_false,
                       std::vector<std::string> bools_toggle);

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
    std::unordered_map<std::string, int> m_counter_set;
    std::unordered_map<std::string, int> m_counters_increment;
    std::vector<std::string> m_bools_true;
    std::vector<std::string> m_bools_false;
    std::vector<std::string> m_bools_toggle;
    void OnCollision(std::shared_ptr<CollisionComponent> other);
};

#endif
