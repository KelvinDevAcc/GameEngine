#pragma once
#include <map>

#include "Singleton.h"

struct PlayerData {
    int score = 0;
    int lives = 3;
    int pepperCount = 5;
};

class GameData : public dae::Singleton<GameData> {
public:
    GameData() : m_gameState(GameState::SINGLE_PLAYER) {}

    // Method to find all players and store their data
    void FindAndStorePlayerData();

    // Method to retrieve player data by player ID
    PlayerData GetPlayerData(int playerID) const;

    // Method to update player data by player ID
    void UpdatePlayerData(int playerID, const PlayerData& newData);

    int GetNumberOfPlayers() const;

    // Method to reset player data by player ID
    void ResetPlayerData(int playerID);

    enum class GameState { SINGLE_PLAYER, MULTIPLAYER, VERSUS };
    GameState GetGameState() const { return m_gameState; }
    void SetGameState(GameState gameState) { m_gameState = gameState; }

private:
    // Private constructor to prevent instantiation

    std::map<int, PlayerData> m_playerData;

    // Private data members
    GameState m_gameState;
};

