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

    /**
     * @brief Know if the game has quit or not
     *
     * @return true
     * @return false
     */
    static bool IsQuit();

    /**
     * @brief Set the Quit game boolean
     *
     */
    bool m_isQuit = false;

   private:
    static GameManager &instance();
    GameManager() = default;
    // ~GameManager() = default;
    GameManager(const GameManager &) = delete;
    GameManager &operator=(const GameManager &) = delete;
};