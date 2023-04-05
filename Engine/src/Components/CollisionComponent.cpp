#include "./Components/CollisionComponent.hpp"

CollisionComponent::CollisionComponent(std::string objectType, std::shared_ptr<TransformComponent> transformer, int width, int height)
{
    m_objectType = objectType;
    m_transformer = transformer;
    m_height = height;
    m_width = width;
}

CollisionComponent::~CollisionComponent()
{
}

ObjectType CollisionComponent::GetType(std::string inString)
{
    if (inString == "player")
        return player;
    if (inString == "wall")
        return wall;
    if (inString == "enemy")
        return enemy;
    if (inString == "interactable")
        return interactable;
    return player;
}

void CollisionComponent::Update()
{
    if (m_objectType == "wall" || m_objectType == "interactable")
    {
        return;
    }
    // string -> objectID
    // player: dynamic, enemy: dynamic, wall: static, pac:static
    std::map<std::string, std::shared_ptr<GameObject>> list =
        GameObjectManager::instance().m_gameobjects;
    // Get collision

    std::map<std::string, std::shared_ptr<CollisionComponent>> collision_components_list;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        collision_components_list.emplace(it->first,
                                          std::dynamic_pointer_cast<CollisionComponent>(it->second->m_components["3CollisionComponent"]));
    }

    for (auto it = collision_components_list.begin(); it != collision_components_list.end(); it++)
    {
        // check if equal itself
        Vec2 penetration;
        // ('std::shared_ptr<CollisionComponent>' and 'CollisionComponent *')
        // static:
        if (m_objectType == it->second->m_objectType)
        {
            continue;
        }
        // dynamic
        else
        {
            if (m_objectType == "player")
            {
                switch (GetType(it->second->m_objectType))
                {
                case wall:
                {
                    std::cout << "player with wall" << std::endl;
                    Vec2 penetration = CheckCollision(it->second);
                    std::cout << "penetration: " << penetration.x << " " << penetration.y << std::endl;
                    m_transformer->m_position += penetration;
                    break;
                }
                case interactable:
                {
                    GameObjectManager::instance().RemoveGameObject(it->first);
                    break;
                }

                case enemy:
                {
                    // TODO: Game over!
                    // GameObjectManager::instance().removeObject(this);
                    break;
                }

                default:
                {
                }
                }
            }
            else
            {
                // enemy + player / enemy + enemy/ enemy + wall
                switch (GetType(it->second->m_objectType))
                {
                case wall:
                {
                    Vec2 penetration = CheckCollision(it->second);
                    m_transformer->m_position += penetration;
                    break;
                }

                case player:
                {
                    // Game over
                    break;
                }

                default:
                {
                }
                }
            }
        }
    }
}

Vec2 CollisionComponent::CheckCollision(std::shared_ptr<CollisionComponent> other)
{
    Vec2 penetration(0, 0);

    float other_left = other->m_transformer->m_position.x;
    float other_right = other->m_transformer->m_position.x + other->m_width;
    float other_top = other->m_transformer->m_position.y;
    float other_bottom = other->m_transformer->m_position.y + other->m_height;

    float this_left = m_transformer->m_position.x;
    float this_right = m_transformer->m_position.x + m_width;
    float this_top = m_transformer->m_position.y;
    float this_bottom = m_transformer->m_position.y + m_height;

    if (this_right <= other_left || this_left >= other_right || this_bottom <= other_top || this_top >= other_bottom)
    {
        return penetration;
    }
    else
    {

        if (this_right > other_left)
        {
            // this object is colliding others from left to right
            penetration.x = other_left - this_right;
        }
        else if (this_left < other_right)
        {
            penetration.x = other_right - this_left;
        }
        // penetration.x = other->m_transformer->m_position.x - m_transformer->m_position.x;

        if (this_bottom > other_top)
        {
            // this object is colliding others from top to bottom
            // penetration should be negative
            penetration.y = other_top - this_bottom;
        }
        else if (this_top < other_bottom)
        {
            penetration.y = other_bottom - this_top;
        }
    }

    return penetration;
}