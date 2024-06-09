#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "EnemyAIComponent.h"
#include "GameTime.h"

#include "LoadMap.h"

struct PairHash {
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U>& pair) const {
        // Combine the hashes of the two elements in the pair
        return std::hash<T>()(pair.first) ^ std::hash<U>()(pair.second);
    }
};
struct NodeRecord
{
    SDL_Rect* pNode = nullptr;
    float costSoFar = 0.f;
    float estimatedTotalCost = 0.f;

    bool operator==(const NodeRecord& other) const
    {
        return pNode == other.pNode
            && costSoFar == other.costSoFar
            && estimatedTotalCost == other.estimatedTotalCost;
    }

    bool operator<(const NodeRecord& other) const
    {
        return estimatedTotalCost < other.estimatedTotalCost;
    }
};

class MrHotDogAIComponent : public dae::Component
{
public:
    MrHotDogAIComponent(dae::GameObject* owner, std::vector<std::vector<char>>& loadMap);
    ~MrHotDogAIComponent() = default;

    void Update() override;

    

    glm::vec3 GetMoveDirection() const
    {
        return m_moveDirection;
    }

    std::type_info const& GetComponentType() const override { return typeid(MrHotDogAIComponent); }

private:
    std::vector<SDL_Rect*> CalculatePathToPeter(const glm::vec3& position);
    std::vector<std::pair<int, int>> GetNeighbors(const std::pair<int, int>& node) const;
    std::vector<SDL_Rect*> ReconstructPath(const std::unordered_map<std::pair<int, int>, std::pair<int, int>, PairHash>& cameFrom, const std::pair<int, int>& current);
    //bool IsCenteredOnLadder(dae::GameObject& gameObject) const;
    bool IsCellWalkable(int x, int y) const;
    float GetCost(const std::pair<int, int>& next) const;
    float GetHeuristicCost(const std::pair<int, int>& pNodeA, const std::pair<int, int>& pNodeB);

    std::vector<std::unique_ptr<SDL_Rect>> m_path;
    std::vector<std::unique_ptr<SDL_Rect>> m_gridCells;

    float m_movementSpeed = 20.f;
    dae::GameObject* m_gameObject;
    glm::vec2 m_cellSize;
    glm::vec2 m_minCoords;
    glm::vec2 m_maxCoords;
    glm::vec3 m_moveDirection;
    int m_numCellsX;
    int m_numCellsY;
    SDL_Rect* m_startNode;
    SDL_Rect* m_goalNode;
    std::vector<std::vector<char>> m_map;
};



