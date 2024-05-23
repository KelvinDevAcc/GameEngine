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


private:
    void loadFromFile(const std::string& mapFilePath, const std::string& ingFilePath);
    void printMap(const std::vector<std::vector<char>>& mapToPrint) const;

    std::vector<std::vector<char>> map;
    std::vector<std::vector<char>> ingMap;
};
