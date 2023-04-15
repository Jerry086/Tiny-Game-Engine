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

    virtual void SetPython(py::module_& python);

   protected:
    std::string m_pythonScriptPath;
    // py::module_ m_python{py::none()};
    py::module_ m_python;

   private:
    const int m_type = Component_TYPE;
};

#endif