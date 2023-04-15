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
     * @brief Obtain the instance of the GameManager
     *
     * @return GameManager& instance
     */
    static GameManager &instance();

    /**
     * @brief Shutdown the GameManager
     *
     */
    void ShutDown() override;

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
    GameManager() = default;
    // ~GameManager() = default;
    GameManager(const GameManager &) = delete;
    GameManager &operator=(const GameManager &) = delete;
};