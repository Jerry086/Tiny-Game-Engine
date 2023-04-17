#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <unordered_map>
#include <vector>

#include "./Components/BehaviorComponent.hpp"
#include "./Components/CollisionComponent.hpp"
#include "./Components/Component.hpp"
#include "./Components/ControllerComponent.hpp"
#include "./Components/HealthBarComponent.hpp"
#include "./Components/SpriteComponent.hpp"
#include "./Components/TransformComponent.hpp"
#include "./Services/GameManager.hpp"
#include "./Services/GameObjectManager.hpp"
#include "GameObject.hpp"
#include "SDLGraphicsProgram.h"

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::unordered_map<std::string, int>);
PYBIND11_MAKE_OPAQUE(std::vector<std::string>);
PYBIND11_MAKE_OPAQUE(std::map<std::string, std::shared_ptr<GameObject>>);

// Creates a macro function that will be called
// whenever the module is imported into python
// 'mygameengine' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'
PYBIND11_MODULE(mygameengine, m) {
    m.doc() = "our game engine as a library";

    py::class_<std::string>(m, "String").def(py::init<const char *>());
    py::bind_map<std::map<std::string, std::shared_ptr<GameObject>>>(
        m, "StringGameObjectMap");

    py::class_<SDLGraphicsProgram>(m, "SDLGraphicsProgram")
        .def(py::init<int, int>(), py::arg("w"), py::arg("h"))
        .def("clear", &SDLGraphicsProgram::clear)
        .def("delay", &SDLGraphicsProgram::delay)
        .def("flip", &SDLGraphicsProgram::flip)
        .def("DrawRectangle", &SDLGraphicsProgram::DrawRectangle)
        .def("DrawPoint", &SDLGraphicsProgram::DrawPoint)
        .def("ShutDown", &SDLGraphicsProgram::ShutDown);

    py::class_<GameObject, std::shared_ptr<GameObject>>(m, "GameObject")
        .def(py::init<const std::string &>(), py::arg("id"))
        .def("Update", &GameObject::Update)
        .def("Render", &GameObject::Render)
        .def("StartUp", &GameObject::StartUp)
        .def("ShutDown", &GameObject::ShutDown)
        .def("AddComponent", &GameObject::AddComponent)
        .def("GetComponent", &GameObject::GetComponent)
        .def("GetControllerComponents",
             &GameObject::GetComponentsPython<ControllerComponent>)
        .def("SetPythonScriptModuleName",
             &GameObject::SetPythonScriptModuleName)
        .def_readwrite("m_enabled", &GameObject::m_enabled)
        .def_readwrite("m_name", &GameObject::m_name);

    py::class_<GameObjectManager,
               std::unique_ptr<GameObjectManager, py::nodelete>>(
        m, "GameObjectManager")
        .def(py::init([]() {
            return std::unique_ptr<GameObjectManager, py::nodelete>(
                &GameObjectManager::instance());
        }))
        .def("StartUp", &GameObjectManager::StartUp)
        .def("ShutDown", &GameObjectManager::ShutDown)
        .def("Update", &GameObjectManager::Update)
        .def("Render", &GameObjectManager::Render)
        .def("AddGameObject", &GameObjectManager::AddGameObject)
        .def("RemoveGameObject", &GameObjectManager::RemoveGameObject)
        .def("GetGameObject", &GameObjectManager::GetGameObject)
        .def("ShutDown", &GameObjectManager::ShutDown)
        .def_readwrite("m_gameobjects", &GameObjectManager::m_gameobjects);
    // .def("GetAllGameObjects", [](GameObjectManager &self) {
    //     std::vector<std::pair<std::string, std::shared_ptr<GameObject>>>
    //         pairs;
    //     for (const auto &pair : self.m_gameobjects) {
    //         pairs.push_back(pair);
    //     }
    //     return pairs;
    // });

    py::class_<Vec2>(m, "Vec2")
        .def(py::init<float, float>(), py::arg("x"), py::arg("y"))
        .def_readwrite("x", &Vec2::x)
        .def_readwrite("y", &Vec2::y)
        .def("__add__", &Vec2::operator+)
        .def("__iadd__", &Vec2::operator+=)
        .def("__mul__", &Vec2::operator*);

    py::class_<Component, std::shared_ptr<Component>>(m, "Component")
        .def(py::init<>())
        .def_readwrite("m_enabled", &Component::m_enabled)
        .def_readwrite("m_name", &Component::m_name);

    py::class_<ControllerComponent, Component,
               std::shared_ptr<ControllerComponent>>(m, "ControllerComponent")
        .def(py::init<>());

    py::class_<BehaviorComponent, Component,
               std::shared_ptr<BehaviorComponent>>(m, "BehaviorComponent")
        .def(py::init<>());

    py::class_<TransformComponent, Component,
               std::shared_ptr<TransformComponent>>(m, "TransformComponent")
        .def(py::init<Vec2 &>(), py::arg("position"))
        .def(py::init<Vec2 &, Vec2 &, std::shared_ptr<ControllerComponent> &>(),
             py::arg("direction"), py::arg("position"),
             py::arg("controllerComponent"))
        .def(py::init<Vec2 &, Vec2 &, std::shared_ptr<BehaviorComponent> &>(),
             py::arg("direction"), py::arg("position"),
             py::arg("controllerComponent"))
        .def_readwrite("m_position", &TransformComponent::m_position)
        .def_readwrite("m_speed", &TransformComponent::m_speed);

    py::class_<SpriteComponent, Component, std::shared_ptr<SpriteComponent>>(
        m, "SpriteComponent")
        .def(
            py::init<const std::string &, std::shared_ptr<TransformComponent> &,
                     int, int, int, int, int, int, int>(),
            py::arg("filename"), py::arg("transformComponent"), py::arg("x"),
            py::arg("y"), py::arg("w"), py::arg("h"), py::arg("frames"),
            py::arg("numRows"), py::arg("numCols"))
        .def(
            py::init<const std::string &, std::shared_ptr<TransformComponent> &,
                     int, int, int, int, int, int, int, int, int>(),
            py::arg("filename"), py::arg("transformComponent"), py::arg("x"),
            py::arg("y"), py::arg("w"), py::arg("h"), py::arg("frames"),
            py::arg("numRows"), py::arg("numCols"), py::arg("forceScreenWidth"),
            py::arg("forceScreenHeight"))
        .def(
            py::init<const std::string &, std::shared_ptr<TransformComponent> &,
                     int, int, int, int, int, int, int, int, int, int, int>(),
            py::arg("filename"), py::arg("transformComponent"), py::arg("x"),
            py::arg("y"), py::arg("w"), py::arg("h"), py::arg("frames"),
            py::arg("numRows"), py::arg("numCols"), py::arg("forceScreenWidth"),
            py::arg("forceScreenHeight"), py::arg("srcXOffset"),
            py::arg("srcYOffset"));

    py::class_<HealthBarComponent, Component,
               std::shared_ptr<HealthBarComponent>>(m, "HealthBarComponent")
        .def(
            py::init<const std::string &, std::shared_ptr<TransformComponent> &,
                     int, int, int, int, int>(),
            py::arg("filename"), py::arg("transformComponent"), py::arg("w"),
            py::arg("h"), py::arg("frames"), py::arg("numRows"),
            py::arg("numCols"))
        .def("SetHealth", &HealthBarComponent::SetHealth);

    py::class_<CollisionComponent, Component,
               std::shared_ptr<CollisionComponent>>(m, "CollisionComponent")
        .def(py::init<const std::string &,
                      const std::shared_ptr<TransformComponent> &, int, int>(),
             py::arg("objectType"), py::arg("transformComponent"), py::arg("w"),
             py::arg("h"));

    py::class_<ServiceLocator>(m, "ServiceLocator")
        .def_static("Update", &ServiceLocator::Update)
        .def_static("ResetAllServices", &ServiceLocator::ResetAllServices)
        .def_static("Render", &ServiceLocator::Render);

    py::class_<GameManager>(m, "GameManager")
        .def_static("IsQuit", &GameManager::IsQuit);

    py::class_<VariableManager>(m, "VariableManager")
        .def_static("GetBool", &VariableManager::GetBool)
        .def_static("GetCounter", &VariableManager::GetCounter)
        .def_static("SetBool", &VariableManager::SetBool)
        .def_static("SetCounter", &VariableManager::SetCounter)
        .def_static("IncrementCounter", &VariableManager::IncrementCounter)
        .def_static("ToggleBool", &VariableManager::ToggleBool)
        .def_static("GetDict", &VariableManager::GetDict)
        .def_static("SetDict", &VariableManager::SetDict);
}
