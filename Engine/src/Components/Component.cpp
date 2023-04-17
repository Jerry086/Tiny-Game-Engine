#include "./Components/Component.hpp"

#include "GameObject.hpp"
/**
 * Constructor
 */
Component::Component() {}
/**
 * Destructor
 */
Component::~Component() {}
/**
 * Get the type of the component
 */
int Component::GetType() { return m_type; }

void Component::SetPython(py::module_& python) { m_python = python; }

void Component::SetParent(std::shared_ptr<GameObject> parent) {
    m_parent = parent;
}