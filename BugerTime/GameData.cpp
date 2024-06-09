#include "GameData.h"

#include "Command.h"
#include "Player.h"
#include "SceneData.h"

void GameData::FindAndStorePlayerData() {
	const std::vector<dae::GameObject*> players = dae::SceneData::GetInstance().GetPlayers();

    // Reset player data map
    m_playerData.clear();

    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        if (!players[i]) {
            // Handle null pointer (if it can occur)
            continue;
        }

        // Check if the player has the required components
        auto pointComponent = players[i]->GetComponent<dae::PointComponent>();
        auto healthComponent = players[i]->GetComponent<dae::HealthComponent>();

        if (!pointComponent || !healthComponent) {
            // Skip player if missing required components
            continue;
        }

        // Store player data
        PlayerData playerData;
        playerData.score = pointComponent->GetScore();
        playerData.lives = healthComponent->GetLives();

        // Store player data in the map with player ID as key
        m_playerData[i] = playerData;
    }
}

int GameData::GetNumberOfPlayers() const {
    return static_cast<int>(m_playerData.size());
}

// Method to retrieve player data by player ID
PlayerData GameData::GetPlayerData(int playerID) const {
    // Check if player ID exists in the map
    if (m_playerData.find(playerID) != m_playerData.end()) {
        return m_playerData.at(playerID);
    }
    else {
        // Return default player data if player ID not found
        return PlayerData(); // Assuming PlayerData has a default constructor
    }
}

// Method to update player data by player ID
void GameData::UpdatePlayerData(int playerID, const PlayerData& newData) {
    // Update player data if player ID exists in the map
    if (m_playerData.find(playerID) != m_playerData.end()) {
        m_playerData[playerID] = newData;
    }
    // Otherwise, do nothing (or log an error message)
}

// Method to reset player data by player ID
void GameData::ResetPlayerData(int playerID) {
    // Reset player data if player ID exists in the map
    if (m_playerData.find(playerID) != m_playerData.end()) {
        m_playerData[playerID] = PlayerData(); // Assuming PlayerData has a default constructor
    }
    // Otherwise, do nothing (or log an error message)
}