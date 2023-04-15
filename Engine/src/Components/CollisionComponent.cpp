#include "./Components/CollisionComponent.hpp"

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
    if (m_objectType_enum == wall || m_objectType_enum == interactable ||
        m_objectType_enum == none)
        return;

    // get the list of game objects
    std::map<std::string, std::shared_ptr<GameObject>> list =
        GameObjectManager::instance().m_gameobjects;

    // detect collisions, O(n^2)
    for (auto it = list.begin(); it != list.end(); it++) {
        std::vector<std::shared_ptr<CollisionComponent>> collisionComponents =
            it->second->GetComponents<CollisionComponent>();
        if (collisionComponents.size() == 0) continue;

        std::shared_ptr<CollisionComponent> other = collisionComponents[0];
        // continue if the object is not collidable or the object is itself
        if (other == nullptr || m_objectType_enum == other->m_objectType_enum)
            continue;

        if (m_objectType_enum == player) {
            switch (other->m_objectType_enum) {
                case wall: {
                    Vec2 penetration = CheckCollision(other);
                    m_transformer->m_position += penetration;
                    break;
                }

                case interactable: {
                    Vec2 penetration = CheckCollision(other);
                    if (penetration.x != 0 || penetration.y != 0)
                        GameObjectManager::instance().RemoveGameObject(
                            it->first);
                    break;
                }

                case enemy: {
                    // TODO: add player death animation
                    Vec2 penetration = CheckCollision(other);
                    if (penetration.x != 0 || penetration.y != 0) {
                        std::cout << "Game Over" << std::endl;
                        GameObjectManager::instance().Shutdown();
                    }
                    break;
                }

                default: {
                }
            }
        } else {
            // enemy + player / enemy + wall
            switch (other->m_objectType_enum) {
                case wall: {
                    Vec2 penetration = CheckCollision(other);
                    m_transformer->m_position += penetration;
                    break;
                }

                    // case player: {
                    //     // TODO: add player death animation
                    //     GameObjectManager::instance().Shutdown();
                    //     std::cout << "Game Over" << std::endl;
                    //     break;
                    // }

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
        if (m_controller->GetDirectionX() > 0)
            penetration.x = other_left - this_right;
        else if (m_controller->GetDirectionX() < 0)
            penetration.x = other_right - this_left;
        else if (m_controller->GetDirectionY() > 0)
            penetration.y = other_top - this_bottom;
        else if (m_controller->GetDirectionY() < 0)
            penetration.y = other_bottom - this_top;
    }

    return penetration;
}

/**
 * Getter of the component type
 */
int CollisionComponent::GetType() { return m_type; }