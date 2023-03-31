#ifndef COMPONENT_HPP 
#define COMPONENT_HPP

#include<iostream>

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

class Component{
    public:
        Component();
        ~Component();

        virtual void Update() = 0;
        virtual void Render()=0;

    private:

};


#endif
