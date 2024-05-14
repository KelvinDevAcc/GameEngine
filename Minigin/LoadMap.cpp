#include "LoadMap.h"
#include <iostream>
#include <fstream>

LoadMap::LoadMap(const std::string& filePath) {
    loadFromFile(filePath);
}

void LoadMap::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<char> row(line.begin(), line.end());
        map.push_back(row);
    }

    file.close();
}

void LoadMap::printMap() const {
    for (const auto& row : map) {
        for (const char tile : row) {
            std::cout << tile;
        }
        std::cout << std::endl;
    }
}

const std::vector<std::vector<char>>& LoadMap::getMap() const {
    return map;
}