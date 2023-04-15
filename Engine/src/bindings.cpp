#include <pybind11/pybind11.h>

#include "./Components/BehaviorComponent.hpp"
#include "./Components/CollisionComponent.hpp"
#include "./Components/Component.hpp"
#include "./Components/ControllerComponent.hpp"
#include "./Components/CounterComponent.hpp"
#include "./Components/HealthBarComponent.hpp"
#include "./Components/SpriteComponent.hpp"
#include "./Components/TransformComponent.hpp"
#include "./Services/GameManager.hpp"
#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "SDLGraphicsProgram.h"

namespace py = pybind11;

// Creates a macro function that will be called
// whenever the module is imported into python
// 'mygameengine' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'
PYBIND11_MODULE(mygameengine, m) {
    m.doc() = "our game engine as a library";

    py::class_<SDLGraphicsProgram>(m, "SDLGraphicsProgram")
        .def(py::init<int, int>(), py::arg("w"), py::arg("h"))
        .def("clear", &SDLGraphicsProgram::clear)
        .def("delay", &SDLGraphicsProgram::delay)
        .def("flip", &SDLGraphicsProgram::flip)
        .def("DrawRectangle", &SDLGraphicsProgram::DrawRectangle)
        .def("DrawPoint", &SDLGraphicsProgram::DrawPoint);

    py::class_<GameObject, std::shared_ptr<GameObject>>(m, "GameObject")
        .def(py::init<const std::string &>(), py::arg("id"))
        .def("Update", &GameObject::Update)
        .def("Render", &GameObject::Render)
        .def("StartUp", &GameObject::StartUp)
        .def("ShutDown", &GameObject::ShutDown)
        .def("AddComponent", &GameObject::AddComponent)
        .def("GetComponent", &GameObject::GetComponent)
        .def("GetControllerComponents",
             &GameObject::GetComponentsPython<ControllerComponent>);

    py::class_<GameObjectManager,
               std::unique_ptr<GameObjectManager, py::nodelete>>(
        m, "GameObjectManager")
        .def(py::init([]() {
            return std::unique_ptr<GameObjectManager, py::nodelete>(
                &GameObjectManager::instance());
        }))
        .def("Update", &GameObjectManager::Update)
        .def("Render", &GameObjectManager::Render)
        .def("AddGameObject", &GameObjectManager::AddGameObject)
        .def("RemoveGameObject", &GameObjectManager::RemoveGameObject)
        .def("GetGameObject", &GameObjectManager::GetGameObject);

    py::class_<Vec2>(m, "Vec2")
        .def(py::init<float, float>())
        .def_readwrite("x", &Vec2::x)
        .def_readwrite("y", &Vec2::y)
        .def("__add__", &Vec2::operator+)
        .def("__iadd__", &Vec2::operator+=)
        .def("__mul__", &Vec2::operator*);

    py::class_<Component, std::shared_ptr<Component>>(m, "Component")
        .def(py::init<>());

    py::class_<ControllerComponent, Component,
               std::shared_ptr<ControllerComponent>>(m, "ControllerComponent")
        .def(py::init<>())
        .def("QuitProgram", &ControllerComponent::QuitProgram);

    py::class_<BehaviorComponent, Component,
               std::shared_ptr<BehaviorComponent>>(m, "BehaviorComponent")
        .def(py::init<>());

    py::class_<TransformComponent, Component,
               std::shared_ptr<TransformComponent>>(m, "TransformComponent")
        .def(py::init<Vec2 &>(), py::arg("new_position"))
        .def(py::init<Vec2 &, Vec2 &, std::shared_ptr<ControllerComponent> &>(),
             py::arg("direction"), py::arg("new_position"),
             py::arg("controller"))
        .def(py::init<Vec2 &, Vec2 &, std::shared_ptr<BehaviorComponent> &>(),
             py::arg("direction"), py::arg("new_position"),
             py::arg("controller"))
        .def_readwrite("m_position", &TransformComponent::m_position)
        .def_readwrite("m_speed", &TransformComponent::m_speed);

    py::class_<SpriteComponent, Component, std::shared_ptr<SpriteComponent>>(
        m, "SpriteComponent")
        .def(
            py::init<const std::string &, std::shared_ptr<TransformComponent> &,
                     int, int, int, int, int, int, int>(),
            py::arg("filename"), py::arg("transformComponent"), py::arg("x"),
            py::arg("y"), py::arg("w"), py::arg("h"), py::arg("frames"),
            py::arg("numRows"), py::arg("numCols"));

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
                      std::shared_ptr<TransformComponent> &, int, int>(),
             py::arg("objectType"), py::arg("transformComponent"), py::arg("w"),
             py::arg("h"));

    py::class_<CounterComponent, Component, std::shared_ptr<CounterComponent>>(
        m, "CounterComponent")
        .def(py::init<>())
        .def("SetCounter", &CounterComponent::SetCounter)
        .def("GetCounter", &CounterComponent::GetCounter)
        .def("RemoveCounter", &CounterComponent::RemoveCounter);

    py::class_<ServiceLocator>(m, "ServiceLocator")
        .def_static("Update", &ServiceLocator::Update);

    py::class_<GameManager>(m, "GameManager")
        .def_static("IsQuit", &GameManager::IsQuit);
}
