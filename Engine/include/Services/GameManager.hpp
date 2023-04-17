#pragma once
#include "IService.hpp"

/**
 * @brief The GameManager class that manages the game state
 *
 */
class GameManager : public IService {
    friend class ServiceLocator;

   public:
    /**
     * @brief Shutdown the GameManager
     *
     */
    void ShutDown() override;

    void StartUp() override;

    /**
     * @brief Update the GameManager
     *
     */
    void Update() override;

    static bool IsQuit();
    static bool IsGameOver();

    static void ShowGameOverPopup();

    bool m_isQuit = false;
    bool m_isGameOver = false;

   private:
    /**
     * @brief Obtain the instance of the GameManager
     *
     * @return GameManager& instance
     */
    static GameManager &instance();
    GameManager() = default;
    // ~GameManager() = default;
    GameManager(const GameManager &) = delete;
    GameManager &operator=(const GameManager &) = delete;
};