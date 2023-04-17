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
GameObject::GameObject(std::string id) : m_name(id) {}
/**
 * Destructor for the GameObject class
 */
GameObject::~GameObject() {}
/**
 * StartUp the game object
 */
void GameObject::StartUp() {
    if (m_pythonScriptModuleName != "") {
        // Alternatively, you can load a script from a file
        // py::eval_file(script_path.c_str(), py::globals(), py::dict());
        // py::eval_file(m_pythonScriptPath, py::globals());
        m_python = py::module_::import(m_pythonScriptModuleName.c_str());
    }
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        if (m_pythonScriptModuleName != "") it->second->SetPython(m_python);
        it->second->StartUp();
    }
}
/**
 * ShutDown the game object by clearing the components map
 */
void GameObject::ShutDown() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        it->second->ShutDown();
    }
    m_components.clear();
}
/**
 * Update the game object by iterating through all the components and
 * calling their Update function. The components are stored in a ordered
 * map, with the key being the id of the component. The order to update
 * the components is important, as some components may depend
 */
void GameObject::Update() {
    if (!m_enabled) return;
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        if (!it->second->m_enabled) continue;
        it->second->Update();

        std::string pythonCompName = ConvertToPythonName(it->first) + "_update";
        if (m_python && py::hasattr(m_python, pythonCompName.c_str())) {
            m_python.attr(pythonCompName.c_str())();
        }
    }

    if (m_python && py::hasattr(m_python, "game_object_update")) {
        m_python.attr("game_object_update")();
    }
}
/**
 * Render the game object by iterating through all the components and
 * calling their Render function. The components are stored in a ordered
 * map, with the key being the id of the component. The order to render
 * the components is important, as some components may depend
 */
void GameObject::Render() {
    if (!m_enabled) return;
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        if (!it->second->m_enabled) continue;
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
    component->m_name = componentName;
    component->SetParent(std::make_shared<GameObject>(*this));
}
/**
 * Remove a component from the game object given the component name
 */
void GameObject::RemoveComponent(std::string componentName) {
    std::cout << "Removing " << componentName << std::endl;
    auto it = m_components.find(componentName);
    if (it != m_components.end()) {
        it->second->SetParent(nullptr);
    }
    m_components.erase(componentName);

    std::cout << "Removing complete" << componentName << std::endl;
}
/**
 * Get a component from the game object given the component name
 */
std::shared_ptr<Component> GameObject::GetComponent(std::string componentName) {
    return m_components[componentName];
}

void GameObject::SetPythonScriptModuleName(std::string name) {
    m_pythonScriptModuleName = name;
}

std::string GameObject::ConvertToPythonName(std::string name) {
    size_t pos = name.find_last_of('_');
    if (pos == std::string::npos) {
        return "";
    }

    std::string result = name.substr(pos + 1);
    for (size_t i = 0; i < result.size(); ++i) {
        if (isupper(result[i])) {
            result[i] = tolower(result[i]);
            if (i > 0) {
                result.insert(i, "_");
                ++i;
            }
        }
    }
    return result;
}