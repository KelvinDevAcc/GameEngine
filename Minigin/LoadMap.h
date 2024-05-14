#pragma once
#include <vector>
#include <string>

class LoadMap {
public:
    LoadMap(const std::string& filePath);
    void printMap() const;
    const std::vector<std::vector<char>>& getMap() const;

private:
    std::vector<std::vector<char>> map;
    void loadFromFile(const std::string& filePath);
};

