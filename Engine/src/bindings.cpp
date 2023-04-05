#include "./Components/Component.hpp"
#include "./Components/ControllerComponent.hpp"
#include "./Components/HealthBarComponent.hpp"
#include "./Components/SpriteComponent.hpp"
#include "./Components/TileMapComponent.hpp"
#include "./Components/TransformComponent.hpp"
#include "./Components/CollisionComponent.hpp"
#include "./Components/BehaviorComponent.hpp"
#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "SDLGraphicsProgram.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

// Creates a macro function that will be called
// whenever the module is imported into python
// 'mygameengine' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'
PYBIND11_MODULE(mygameengine, m)
{
    m.doc() = "our game engine as a library"; // Optional docstring

    py::class_<SDLGraphicsProgram>(m, "SDLGraphicsProgram")
        .def(py::init<int, int>(), py::arg("w"),
             py::arg("h"))                        // our constructor
        .def("clear", &SDLGraphicsProgram::clear) // Expose member methods
        .def("delay", &SDLGraphicsProgram::delay)
        .def("flip", &SDLGraphicsProgram::flip)
        .def("getKeyAction", &SDLGraphicsProgram::getKeyAction)
        .def("loop", &SDLGraphicsProgram::loop)
        .def("drawRect", &SDLGraphicsProgram::drawRect)
        .def("DrawPoint", &SDLGraphicsProgram::DrawPoint)
        .def("DrawRectangle", &SDLGraphicsProgram::DrawRectangle);
    // We do not need to expose everything to our users!
    //            .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow,
    //            py::return_value_policy::reference)

    py::class_<GameObject, std::shared_ptr<GameObject>>(m, "GameObject")
        .def(py::init<const std::string &>(), py::arg("id"))
        .def("Update", &GameObject::Update)
        .def("Render", &GameObject::Render)
        .def("StartUp", &GameObject::StartUp)
        .def("ShutDown", &GameObject::ShutDown)
        .def("AddComponent", &GameObject::AddComponent);

    py::class_<Component, std::shared_ptr<Component>>(m, "Component")
        .def(py::init<>());

    py::class_<ControllerComponent, Component,
               std::shared_ptr<ControllerComponent>>(m, "ControllerComponent")
        .def(py::init<>());

    // TODO constructor controller component use shared ptr
    py::class_<TransformComponent, Component,
               std::shared_ptr<TransformComponent>>(m, "TransformComponent")
        .def(py::init<Vec2 &>(),
             py::arg("new_position"))
        .def(py::init<Vec2 &, Vec2 &, std::shared_ptr<ControllerComponent> &>(),
             py::arg("direction"), py::arg("new_position"),
             py::arg("controller"))
        .def(py::init<Vec2 &, Vec2 &, std::shared_ptr<BehaviorComponent> &>(),
             py::arg("direction"), py::arg("new_position"),
             py::arg("controller"))
        .def_readwrite("m_position", &TransformComponent::m_position)
        .def_readwrite("m_speed", &TransformComponent::m_speed);

    // TODO constructor controller component use shared ptr
    py::class_<SpriteComponent, Component, std::shared_ptr<SpriteComponent>>(
        m, "SpriteComponent")
        .def(
            py::init<const std::string &, std::shared_ptr<TransformComponent> &,
                     int, int, int, int, int, int, int>(),
            py::arg("filename"), py::arg("transformComponent"), py::arg("x"),
            py::arg("y"), py::arg("w"), py::arg("h"), py::arg("frames"),
            py::arg("numRows"), py::arg("numCols"))
        // .def("Update", &SpriteComponent::Update)
        .def("SetPosition", &SpriteComponent::SetPosition);

    py::class_<Vec2>(m, "Vec2")
        .def(py::init<float, float>())
        .def_readwrite("x", &Vec2::x)
        .def_readwrite("y", &Vec2::y)
        .def("__add__", &Vec2::operator+)
        .def("__iadd__", &Vec2::operator+=)
        .def("__mul__", &Vec2::operator*);

    py::class_<TileMapComponent, Component, std::shared_ptr<TileMapComponent>>(
        m, "TileMapComponent")
        .def(py::init<std::string &, int, int, int, int, int, int>(),
             py::arg("tileSheetFileName"), py::arg("rows"), py::arg("cols"),
             py::arg("_TileWidth"), py::arg("_TileHeight"), py::arg("_mapX"),
             py::arg("_mapY"));

    py::class_<HealthBarComponent, Component,
               std::shared_ptr<HealthBarComponent>>(m, "HealthBarComponent")
        .def(
            py::init<const std::string &, std::shared_ptr<TransformComponent> &,
                     int, int, int, int>(),
            py::arg("filename"), py::arg("transformComponent"), py::arg("x"),
            py::arg("y"), py::arg("w"), py::arg("h"))
        // .def("Update", &SpriteComponent::Update)
        .def("SetHealth", &HealthBarComponent::SetHealth);

    py::class_<CollisionComponent, Component,
               std::shared_ptr<CollisionComponent>>(m, "CollisionComponent")
        .def(
            py::init<const std::string &, std::shared_ptr<TransformComponent> &, int, int>(),
            py::arg("objectType"), py::arg("transformComponent"), py::arg("w"), py::arg("h"))
        .def("Update", &CollisionComponent::Update);

    py::class_<GameObjectManager, std::unique_ptr<GameObjectManager, py::nodelete>>(m, "GameObjectManager")
        .def(py::init([]()
                      { return std::unique_ptr<GameObjectManager, py::nodelete>(&GameObjectManager::instance()); }))
        .def("Update", &GameObjectManager::Update)
        .def("Render", &GameObjectManager::Render)
        .def("AddGameObject", &GameObjectManager::AddGameObject)
        .def("RemoveGameObject", &GameObjectManager::RemoveGameObject);

    py::class_<BehaviorComponent, Component,
               std::shared_ptr<BehaviorComponent>>(m, "BehaviorComponent")
        .def(
            py::init<>())
        .def("Update", &BehaviorComponent::Update);
}
