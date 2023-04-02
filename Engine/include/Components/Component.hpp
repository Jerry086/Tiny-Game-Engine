#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

class Component {
   public:
    Component();
    virtual ~Component();

    virtual void Update(){};
    virtual void Render(){};

   private:
};

#endif
