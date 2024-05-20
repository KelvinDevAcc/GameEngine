#pragma once
#include <string>
#include <vector>


namespace game
{
	class Player;
}

class LoadMap {
public:
    LoadMap(const std::string& mapFilePath, const std::string& ingFilePath);

    void printMaps() const;
    const std::vector<std::vector<char>>& getMap() const;
    const std::vector<std::vector<char>>& getIngMap() const;

    bool can_entity_move(float move_x, float move_y, const game::Player& player) const;

private:
    void loadFromFile(const std::string& mapFilePath, const std::string& ingFilePath);
    void printMap(const std::vector<std::vector<char>>& mapToPrint) const;

    bool is_obstacle(float x, float y) const;

    bool is_within_bounds(float x, float y) const;

    std::vector<std::vector<char>> map;
    std::vector<std::vector<char>> ingMap;
};
