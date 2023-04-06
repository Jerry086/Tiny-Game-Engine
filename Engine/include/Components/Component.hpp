#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <memory>

class Component
{
public:
   Component();
   virtual ~Component();

   virtual void Update(){};
   virtual void Render(){};

private:
};

#endif
