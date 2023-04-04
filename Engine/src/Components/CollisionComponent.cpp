#include "./Components/CollisionComponent.hpp"

CollisionComponent::CollisionComponent(bool isStatic, int width, int height)
{
    isStatic = isStatic;
    height = height;
    width = width;
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::Update()
{
    //string -> objectID
    // player: dynamic, enemy: dynamic, wall: static, pac:static
    // std::map<std::string, std::shared_ptr<CollisionComponent>> list =
    //     GameObjectManager::instance().collision_objects;
    // for (auto it = list.begin(); it != list.end(); it++)
    // {
    //     // check if equal itself
    //     Vec2 penetration;
    //     if (it->second == this || isStatic == true)
    //     {
    //         continue;
    //     }
    //     else
    //     {
    //         // dynamic + static/ dynamic + dynamic
    //         //  player + enemy
    //         Vec2 penetration = CheckCollision(it->second);
    //         m_transformer += penetration;
    //     }
    // }
}

Vec2 CollisionComponent::CheckCollision(std::shared_ptr<CollisionComponent> other)
{

    Vec2 penetration(0, 0);
    // float projection_x = other->m_transformer.x + other->width;
    // if (m_transformer.x + width < other->m_transformer.x || m_transformer.x > projection_x)
    // {
    //     penetration.x = 0;
    // }
    // else
    // {
    //     penetration.x = other->m_transformer.x - m_transformer.x;
    // }
    // float projection_y = other->m_transformer.y + other->height;
    // if (m_transformer.y + height < other->m_transformer.y || m_transformer.y > projection_y)
    // {
    //     penetration.y = 0;
    // }
    // else
    // {
    //     penetration.y = other->m_transformer.y - m_transformer.y;
    // }
    return penetration;
}
