#include "./Components/Component.hpp"
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
int Component::GetType()
{
    return m_type;
}