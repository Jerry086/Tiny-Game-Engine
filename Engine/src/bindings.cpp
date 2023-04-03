#include "./Components/Component.hpp"
#include "./Components/ControllerComponent.hpp"
#include "./Components/SpriteComponent.hpp"
#include "./Components/TransformComponent.hpp"
#include "GameObject.hpp"
#include "SDLGraphicsProgram.h"
// Include the pybindings
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

    py::class_<GameObject>(m, "GameObject")
        .def(py::init<const std::string &>(), py::arg("id"))
        .def("Update", &GameObject::Update)
        .def("Render", &GameObject::Render)
        .def("StartUp", &GameObject::StartUp)
        .def("ShutDown", &GameObject::ShutDown)
        .def("AddComponent", &GameObject::AddComponent);

    py::class_<Component, std::shared_ptr<Component>>(m, "Component")
        .def(py::init<>());

    py::class_<ControllerComponent, Component, std::shared_ptr<ControllerComponent>>(
        m, "ControllerComponent")
        .def(py::init<>());

    // TODO constructor controller component use shared ptr
    py::class_<TransformComponent, Component,
               std::shared_ptr<TransformComponent>>(m, "TransformComponent")
        .def(py::init<Vec2 &, Vec2 &, std::shared_ptr<ControllerComponent> &>(),
             py::arg("direction"), py::arg("new_position"),
             py::arg("controller"))
        .def_readwrite("m_position", &TransformComponent::m_position)
        .def_readwrite("m_direction", &TransformComponent::m_direction);

    // TODO constructor controller component use shared ptr
    py::class_<SpriteComponent, Component, std::shared_ptr<SpriteComponent>>(
        m, "SpriteComponent")
        .def(py::init<const std::string &, std::shared_ptr<TransformComponent> &, int, int, int,
                      int, int>(),
             py::arg("filename"), py::arg("transformComponent"), py::arg("x"),
             py::arg("y"), py::arg("w"), py::arg("h"), py::arg("frames"))
        // .def("Update", &SpriteComponent::Update)
        .def("SetPosition", &SpriteComponent::SetPosition);

    py::class_<Contact>(m, "Contact")
        .def(py::init<>())
        .def_readwrite("type", &Contact::type)
        .def_readwrite("penetration", &Contact::penetration);

    py::class_<Ball>(m, "Ball")
        .def(py::init<Vec2 &, Vec2 &>(), py::arg("position"),
             py::arg("velocity"))
        .def("Update", &Ball::Update)
        .def("Draw", &Ball::Draw)
        .def("getRect", &Ball::getRect)
        .def("CollideWithPaddle", &Ball::CollideWithPaddle)
        .def("CollideWithWall", &Ball::CollideWithWall);

    py::class_<Paddle>(m, "Paddle")
        .def(py::init<const Vec2 &, const Vec2 &>())
        .def("Update", &Paddle::Update)
        .def("getRect", &Paddle::getRect)
        .def("Draw", &Paddle::Draw)
        .def_readwrite("position", &Paddle::position)
        .def_readwrite("velocity", &Paddle::velocity);

    py::class_<Vec2>(m, "Vec2")
        .def(py::init<float, float>())
        .def_readwrite("x", &Vec2::x)
        .def_readwrite("y", &Vec2::y)
        .def("__add__", &Vec2::operator+)
        .def("__iadd__", &Vec2::operator+=)
        .def("__mul__", &Vec2::operator*);

    m.def("CheckPaddleCollision", &CheckPaddleCollision);
    m.def("CheckWallCollision", &CheckWallCollision);
}
