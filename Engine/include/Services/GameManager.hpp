#pragma once
#include "IService.hpp"

class GameManager : public IService {
    friend class ServiceLocator;

   public:
    static GameManager &instance();
    void ShutDown() override;
    void Update() override;

    static bool IsQuit();

   private:
    bool m_isQuit = false;
    GameManager() = default;
    // ~GameManager() = default;
    GameManager(const GameManager &) = delete;
    GameManager &operator=(const GameManager &) = delete;
};