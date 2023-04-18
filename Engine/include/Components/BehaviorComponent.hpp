#ifndef BEHAVIORCOMPONENT_HPP
#define BEHAVIORCOMPONENT_HPP

#include <memory>

#include "Component.hpp"
#include "Vec.hpp"

/**
 * The BehaviorComponent class that defines the behavior of a game object.
 */
class BehaviorComponent : public Component
{
public:
    /**
     * Constructor
     */
    BehaviorComponent();
    /**
     * Destructor
     */
    ~BehaviorComponent();
    /**
     * Update the moving direction of the game object
     */
    void Update() override;
    /**
     * Getter of current moving direction towards x-axis
     */
    int GetDirectionX();
    /**
     * Getter of current moving direction towards y-axis
     */
    int GetDirectionY();
    /**
     * Getter of the component type
     * @return The type of the component
     */
    int GetType() override;

    int m_direction_x = -1;
    int m_direction_y = 1;

private:
    int counter_x = 0;
    int counter_y = 0;
    const int m_type = BehaviourComponent_TYPE;
};

#endif
