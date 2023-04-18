#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <pybind11/embed.h>

#include <iostream>
#include <memory>
namespace py = pybind11;

#define Component_TYPE 0
#define ControllerComponent_TYPE 1
#define BehaviourComponent_TYPE 1
#define TransformComponent_TYPE 2
#define CollisionComponent_TYPE 3
#define SpriteComponent_TYPE 4
#define HealthBarComponent_TYPE 5
#define CounterComponent_TYPE 6

class GameObject;

/**
 * The Component class that is the base class for all components.
 */
class __attribute__((visibility("default"))) Component {
   public:
    /**
     * Constructor
     */
    Component();
    /**
     * Destructor
     */
    virtual ~Component();
    virtual void StartUp(){};
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

    /**
     * @brief Set the Python module of the component
     *
     * @param python The python module
     */
    virtual void SetPython(py::module_& python);

    /**
     * @brief Set the Parent object
     *
     * @param parent The parent object
     */
    virtual void SetParent(std::shared_ptr<GameObject> parent);

    /**
     * @brief Name of the component
     * @details If properly created, in the format of
     * <The name of parent game object, in any format>_ComponentName
     */
    std::string m_name;

    /**
     * @brief If the component is enabled.
     *
     */
    bool m_enabled{true};

   protected:
    py::module_ m_python;
    std::shared_ptr<GameObject> m_parent;

   private:
    const int m_type = Component_TYPE;
};

#endif