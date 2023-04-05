#include "./Components/CollisionComponent.hpp"

CollisionComponent::CollisionComponent(std::string objectType, int width, int height)
{
    objectType = objectType;
    height = height;
    width = width;
}

CollisionComponent::~CollisionComponent()
{
}


ObjectType CollisionComponent::GetType (std::string inString) {
    if (inString == "player") return player;
    if (inString == "wall") return wall;
    if (inString == "enemy") return enemy;
    if (inString == "interactable") return interactable;
    return player;
}

void CollisionComponent::Update()
{
    // string -> objectID
    // player: dynamic, enemy: dynamic, wall: static, pac:static
    std::map<std::string, std::shared_ptr<GameObject>> list =
        GameObjectManager::instance().collision_objects;
    //Get collision

    std::map<std::string, std::shared_ptr<CollisionComponent>> collision_components_list;
    for (auto it = list.begin(); it != list.end(); it++){
        collision_components_list.emplace(it->first,
        std::dynamic_pointer_cast<CollisionComponent>(it->second->m_components["CollisionComponent"]));
    }

    for (auto it = collision_components_list.begin(); it != collision_components_list.end(); it++)
    {
        // check if equal itself
        Vec2 penetration;
        // ('std::shared_ptr<CollisionComponent>' and 'CollisionComponent *')
        // static:
        if (objectType == it->second->objectType || objectType == "wall" || objectType == "interactable")
        {
            continue;
        }
        // dynamic
        else
        {
            if (objectType == "player")
            {
                switch (GetType(it->second->objectType))
                {
                case wall:
                {
                    Vec2 penetration = CheckCollision(it->second);
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
                switch (GetType(it->second->objectType))
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
    float projection_x = other->m_transformer->m_position.x + other->width;
    if (m_transformer->m_position.x + width < other->m_transformer->m_position.x || m_transformer->m_position.x > projection_x)
    {
        penetration.x = 0;
    }
    else
    {
        if (m_transformer->m_position.x + width > other->m_transformer->m_position.x)
        {
            // this object is colliding others from left to right
            penetration.x = other->m_transformer->m_position.x - m_transformer->m_position.x - width;
        }
        else
        {
            penetration.x = other->m_transformer->m_position.x + other->width - m_transformer->m_position.x;
        }
        // penetration.x = other->m_transformer->m_position.x - m_transformer->m_position.x;
    }

    float projection_y = other->m_transformer->m_position.y + other->height;
    if (m_transformer->m_position.y + height < other->m_transformer->m_position.y || m_transformer->m_position.y > projection_y)
    {
        penetration.y = 0;
    }
    else
    {
        if (m_transformer->m_position.y + height > other->m_transformer->m_position.y)
        {
            // this object is colliding others from left to right
            penetration.y = other->m_transformer->m_position.y - m_transformer->m_position.y - height;
        }
        else
        {
            penetration.y = other->m_transformer->m_position.y + other->height - m_transformer->m_position.y;
        }
    }
    return penetration;
}
