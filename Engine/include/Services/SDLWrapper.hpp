#pragma once

#include <memory>

#include "IService.hpp"
class ServiceLocator;

// TODO HACKYYYYYY
class SDLGraphicsProgram;
class SDLWrapper : public IService {
    friend class ServiceLocator;

   public:
    static SDLWrapper &instance() {
        static SDLWrapper instance;
        return instance;
    }
    void ShutDown() override{};
    std::shared_ptr<SDLGraphicsProgram> m_SDLGraphicsProgram;
    void StartUp(SDLGraphicsProgram &sdl) {
        m_SDLGraphicsProgram = std::make_shared<SDLGraphicsProgram>(sdl);
    }

   private:
    SDLWrapper() = default;
    ~SDLWrapper() = default;
    SDLWrapper(const SDLWrapper &) = delete;
    SDLWrapper &operator=(const SDLWrapper &) = delete;
};