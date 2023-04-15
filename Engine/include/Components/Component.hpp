#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <memory>

#define Component_TYPE 0
#define ControllerComponent_TYPE 1
#define BehaviourComponent_TYPE 1
#define TransformComponent_TYPE 2
#define CollisionComponent_TYPE 3
#define SpriteComponent_TYPE 4
#define HealthBarComponent_TYPE 5
#define CounterComponent_TYPE 6

/**
 * The Component class that is the base class for all components.
 */
class Component {
   public:
    /**
     * Constructor
     */
    Component();
    /**
     * Destructor
     */
    virtual ~Component();
    /**
     * ShutDown the component
     */
    virtual void ShutDown(){};
    /**
     * Update the component
     */
    virtual void Update(){};
    /**
     * Render the component
     */
    virtual void Render(){};
    /**
     * Get the type of the component
     * @return The type of the component
     */
    virtual int GetType();

   private:
    const int m_type = Component_TYPE;
};

#endif