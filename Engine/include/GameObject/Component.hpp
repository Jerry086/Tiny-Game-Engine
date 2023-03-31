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
        virtual void Update(int x, int y, int frame) = 0;
        virtual void Render(SDL_Renderer* ren)=0;
        virtual void SetPosition(float x, float y) = 0;
        virtual void MoveObject(float left, float right) = 0;

    private:

};


#endif
