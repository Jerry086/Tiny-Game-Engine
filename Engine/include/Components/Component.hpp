#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <memory>

/**
 * The Component class that is the base class for all components.
 */
class Component
{
public:
   /**
    * Constructor
    */
   Component();
   /**
    * Destructor
    */
   virtual ~Component();
   /**
    * Update the component
    */
   virtual void Update(){};
   /**
    * Render the component
    */
   virtual void Render(){};
};

#endif