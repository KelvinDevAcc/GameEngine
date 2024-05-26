#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <stdexcept>

class HighScores {
public:
    static constexpr size_t NUM_HIGH_SCORES = 5;
    static constexpr size_t PLAYER_NAME_SIZE = 20;

    HighScores();
    void loadScores();
    void createDefaultScores() const;
    bool isHighScore(uint32_t score) const;
    int highScorePosition(uint32_t score) const;
    uint32_t getTopScore() const;
    void saveNewScore(const std::string& playerName, uint32_t newScore);

    const std::vector<std::pair<std::array<char, PLAYER_NAME_SIZE>, uint32_t>>& getHighScores() const {
        return highScores;
    }

private:
    std::string fileName;
    std::vector<std::pair<std::array<char, PLAYER_NAME_SIZE>, uint32_t>> highScores;
    static constexpr std::array<std::pair<const char*, uint32_t>, NUM_HIGH_SCORES> DEFAULT_SCORES = {
        std::make_pair("Player1", 0),
        std::make_pair("Player2", 0),
        std::make_pair("Player3", 0),
        std::make_pair("Player4", 0),
        std::make_pair("Player5", 100)
    };
};
