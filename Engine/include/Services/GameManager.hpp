#pragma once
#include "IService.hpp"

class GameManager : public IService {
    friend class ServiceLocator;

   public:
    static GameManager &instance();
    void ShutDown() override;
    void Update() override;

    static bool IsQuit();
    static bool IsGameOver();

    static void ShowGameOverPopup();

    bool m_isQuit = false;
    bool m_isGameOver = false;

   private:
    GameManager() = default;
    // ~GameManager() = default;
    GameManager(const GameManager &) = delete;
    GameManager &operator=(const GameManager &) = delete;
};