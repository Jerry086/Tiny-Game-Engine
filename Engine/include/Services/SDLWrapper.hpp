#pragma once

#include <memory>

#include "IService.hpp"
class ServiceLocator;

// TODO HACKYYYYYY
/**
 * @brief Wrapper class to manager SDL and SDLGraphicsProgram with
 * ServiceLocator
 *
 */
class SDLGraphicsProgram;
class SDLWrapper : public IService {
    friend class ServiceLocator;

   public:
    /**
     * @brief Shutdown the SDLWrapper
     *
     */
    void ShutDown() override{};
    /**
     * @brief Start up the SDLWrapper
     *
     */
    void StartUp(SDLGraphicsProgram &sdl) {
        m_SDLGraphicsProgram = std::make_shared<SDLGraphicsProgram>(sdl);
    }

    /**
     * @brief Get the SDLGraphicsProgram object
     *
     */
    std::shared_ptr<SDLGraphicsProgram> m_SDLGraphicsProgram;

   private:
    static SDLWrapper &instance() {
        static SDLWrapper instance;
        return instance;
    }
    SDLWrapper() = default;
    ~SDLWrapper() = default;
    SDLWrapper(const SDLWrapper &) = delete;
    SDLWrapper &operator=(const SDLWrapper &) = delete;
};