#include "GameObject.hpp"
#include <iostream>
GameObject::GameObject(std::string id){
    gameObject_id = id;
}

GameObject::~GameObject(){
}

void GameObject:: StartUp(){
}

void GameObject:: ShutDown(){
}

void GameObject:: Render(){
}

void GameObject:: Update(){
}

void GameObject::AddComponent(std::string componentName, Component component){

}

void GameObject::RemoveComponent(std::string componentName){

}