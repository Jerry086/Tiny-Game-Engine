#include "./Components/CollisionComponent.hpp"

#include <iostream>

#include "./Services/GameManager.hpp"
#include "./Services/ServiceLocator.hpp"
#include "./Services/VariableManager.hpp"
#include "GameObject.hpp"

/**
 * Constructor
 */
CollisionComponent::CollisionComponent(
    std::string objectType, std::shared_ptr<TransformComponent> transformer,
    int width, int height)
    : m_objectType(objectType),
      m_transformer(transformer),
      m_height(height),
      m_width(width) {
    m_controller = transformer->m_controller;
    m_behavior = transformer->m_behavior;
    if (m_objectType == "player")
        m_objectType_enum = player;
    else if (m_objectType == "wall")
        m_objectType_enum = wall;
    else if (m_objectType == "enemy")
        m_objectType_enum = enemy;
    else if (m_objectType == "interactable")
        m_objectType_enum = interactable;
    else if (m_objectType == "none")
        m_objectType_enum = none;
    else {
        std::cout << "Error: Invalid object type" << std::endl;
        m_objectType_enum = none;
    }
}

CollisionComponent::CollisionComponent(
    std::string objectType, std::shared_ptr<TransformComponent> transformer,
    int width, int height, std::unordered_map<std::string, int> counters_set,
    std::unordered_map<std::string, int> counters_increment,
    std::vector<std::string> bools_true, std::vector<std::string> bools_false,
    std::vector<std::string> bools_toggle)
    : m_objectType(objectType),
      m_transformer(transformer),
      m_height(height),
      m_width(width),
      m_counter_set(counters_set),
      m_counters_increment(counters_increment),
      m_bools_true(bools_true),
      m_bools_false(bools_false),
      m_bools_toggle(bools_toggle) {
    m_controller = transformer->m_controller;
    m_behavior = transformer->m_behavior;
    if (m_objectType == "player")
        m_objectType_enum = player;
    else if (m_objectType == "wall")
        m_objectType_enum = wall;
    else if (m_objectType == "enemy")
        m_objectType_enum = enemy;
    else if (m_objectType == "interactable")
        m_objectType_enum = interactable;
    else if (m_objectType == "none")
        m_objectType_enum = none;
    else {
        std::cout << "Error: Invalid object type" << std::endl;
        m_objectType_enum = none;
    }
}

/**
 * Destructor
 */
CollisionComponent::~CollisionComponent() {}

/**
 * Getter of the object type
 */
ObjectType CollisionComponent::GetObjectType() { return m_objectType_enum; }
/**
 * Update the collision component
 * Check collision with other objects
 * Apply the collision response based on the object type
 */
void CollisionComponent::Update() {
    // player: dynamic, enemy: dynamic, wall: static, pac:static
    // ignore static objects
    if (m_objectType_enum == wall || m_objectType_enum == none) return;

    // get the list of game objects
    std::map<std::string, std::shared_ptr<GameObject>> list =
        GameObjectManager::instance().m_gameobjects;

    ServiceLocator::GetService<VariableManager>().SetBool(
        m_name + "_collided_this_frame", false);

    // detect collisions, O(n^2)
    for (auto it = list.begin(); it != list.end(); it++) {
        if (!it->second->m_enabled) {
            continue;
        }

        std::vector<std::shared_ptr<CollisionComponent>> collisionComponents =
            it->second->GetComponents<CollisionComponent>();
        if (collisionComponents.size() == 0) continue;

        std::shared_ptr<CollisionComponent> other = collisionComponents[0];
        // continue if the object is not collidable or the object is itself
        if (other == nullptr || m_objectType_enum == other->m_objectType_enum)
            continue;

        Vec2 penetration = CheckCollision(other);
        if (penetration.x == 0 && penetration.y == 0) continue;
        OnCollision(other);
        if (m_objectType_enum == player) {
            switch (other->m_objectType_enum) {
                case wall: {
                    m_transformer->m_position += penetration;
                    break;
                }

                case interactable: {
                    // GameObjectManager::instance().RemoveGameObject(it->first);
                    // ServiceLocator::GetService<GameObjectManager>()
                    //     .RemoveGameObject(it->first);
                    break;
                }

                case enemy: {
                    ServiceLocator::GetService<VariableManager>().SetBool(
                        "isPacmanGameOver", true);
                    // GameObjectManager::instance().SetGameOver(true);
                    ServiceLocator::GetService<GameObjectManager>().SetGameOver(
                        true);
                    break;
                }

                default: {
                }
            }
        } else {
            // enemy + wall / interactable + wall
            switch (other->m_objectType_enum) {
                case wall: {
                    m_transformer->m_position += penetration;
                    break;
                }

                default: {
                }
            }
        }
    }
}

/**
 * Check collision between two objects
 * Return the penetration vector
 */
Vec2 CollisionComponent::CheckCollision(
    std::shared_ptr<CollisionComponent> other) {
    Vec2 penetration;

    // projected position of the other object
    float other_left = other->m_transformer->m_position.x;
    float other_right = other->m_transformer->m_position.x + other->m_width;
    float other_top = other->m_transformer->m_position.y;
    float other_bottom = other->m_transformer->m_position.y + other->m_height;

    // projected position of this object
    float this_left = m_transformer->m_position.x;
    float this_right = m_transformer->m_position.x + m_width;
    float this_top = m_transformer->m_position.y;
    float this_bottom = m_transformer->m_position.y + m_height;

    // no collision
    if (this_right <= other_left || this_left >= other_right ||
        this_bottom <= other_top || this_top >= other_bottom)
        return penetration;
    else {
        if (m_controller && m_controller->GetDirectionX() > 0 ||
            m_behavior && m_behavior->GetDirectionX() > 0)
            penetration.x = other_left - this_right;
        else if (m_controller && m_controller->GetDirectionX() < 0 ||
                 m_behavior && m_behavior->GetDirectionX() < 0)
            penetration.x = other_right - this_left;
        else if (m_controller && m_controller->GetDirectionY() > 0 ||
                 m_behavior && m_behavior->GetDirectionY() > 0)
            penetration.y = other_top - this_bottom;
        else if (m_controller && m_controller->GetDirectionY() < 0 ||
                 m_behavior && m_behavior->GetDirectionY() < 0)
            penetration.y = other_bottom - this_top;
    }

    return penetration;
}

/**
 * Getter of the component type
 */
int CollisionComponent::GetType() { return m_type; }

void CollisionComponent::OnCollision(
    std::shared_ptr<CollisionComponent> other) {
    ServiceLocator::GetService<VariableManager>().SetBool(
        m_name + "_collided_this_frame", true);

    ServiceLocator::GetService<VariableManager>().SetDict(
        m_name + "_other_name", other->m_name);

    ServiceLocator::GetService<VariableManager>().SetDict(
        m_name + "_other_type", other->m_objectType);

    if (m_python && py::hasattr(m_python, "collision_component_on_collision")) {
        m_python.attr("collision_component_on_collision")();
    }
}