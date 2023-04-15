#include "GameObject.hpp"

#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>
namespace py = pybind11;
/**
 * Constructor for the GameObject class
 * The id of the game object mush be unique
 */
GameObject::GameObject(std::string id) : gameObject_id(id) {}
/**
 * Destructor for the GameObject class
 */
GameObject::~GameObject() {}
/**
 * StartUp the game object
 */
void GameObject::StartUp() {
    // py::gil_scoped_acquire();  // Acquire the GIL since we're creating a
    // Python
    //                            // interpreter

    // // Construct the scoped interpreter guard and store it as a member
    // variable py_guard_ = new py::scoped_interpreter{};

    // Load the Python script file and execute it in the global namespace
    // py::scoped_interpreter guard{};
    // std::string script_path = "./test.py";
    // py::eval_file(script_path.c_str(), py::globals(), py::dict());

    // py::gil_scoped_release();  // Release the GIL since we're done with the
    // Python interpreter
}
/**
 * ShutDown the game object by clearing the components map
 */
void GameObject::ShutDown() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        it->second->ShutDown();
    }
    m_components.clear();

    // py::gil_scoped_acquire();  // Acquire the GIL since we're destroying a
    //                            // Python interpreter

    // delete py_guard_;  // Destroy the scoped interpreter guard

    // py::gil_scoped_release();  // Release the GIL since we're done with the
    //                            // Python interpreter
}
/**
 * Update the game object by iterating through all the components and
 * calling their Update function. The components are stored in a ordered
 * map, with the key being the id of the component. The order to update
 * the components is important, as some components may depend
 */
void GameObject::Update() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        it->second->Update();
    }

    // py::scoped_interpreter guard{};
    // Alternatively, you can load a script from a file
    std::string script_path = "./scripts/test.py";
    // py::eval_file(script_path.c_str(), py::globals(), py::dict());
    py::eval_file("./scripts/test.py", py::globals());

    // Get the update function from the Python script
    py::function update_func = py::globals()["testembed"];

    // Call the update function
    update_func();
}
/**
 * Render the game object by iterating through all the components and
 * calling their Render function. The components are stored in a ordered
 * map, with the key being the id of the component. The order to render
 * the components is important, as some components may depend
 */
void GameObject::Render() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        it->second->Render();
    }
}
/**
 * Add a component to the game object. The component name is used as the
 * key for the component in the map. It must order the components in the
 * right place for the Update and Render functions to work correctly.
 */
void GameObject::AddComponent(std::string componentName,
                              std::shared_ptr<Component> component) {
    if (component->GetType() == CollisionComponent_TYPE) {
        m_collisionComponent = component;
    }
    m_components.emplace(componentName, component);
}
/**
 * Remove a component from the game object given the component name
 */
void GameObject::RemoveComponent(std::string componentName) {
    std::cout << "Removing " << componentName << std::endl;
    m_components.erase(componentName);
    std::cout << "Removing complete" << componentName << std::endl;
}
/**
 * Get a component from the game object given the component name
 */
std::shared_ptr<Component> GameObject::GetComponent(std::string componentName) {
    return m_components[componentName];
}