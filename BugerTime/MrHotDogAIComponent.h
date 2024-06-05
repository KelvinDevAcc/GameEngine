#pragma once
#include <SDL_rect.h>
#include <unordered_map>
#include <glm/geometric.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "EnemyAIComponent.h"
#include "GameTime.h"


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
    MrHotDogAIComponent(dae::GameObject* owner);
    void Update() override;
    void Render() const override;

    std::vector<SDL_Rect*> GetNeighbors(SDL_Rect* pNode);
    float GetCost(SDL_Rect* pNodeA, SDL_Rect* pNodeB);
    float GetHeuristicCost(SDL_Rect* pNodeA, SDL_Rect* pNodeB);

    std::vector<SDL_Rect*> ReconstructPath(const std::unordered_map<SDL_Rect*, SDL_Rect*>& cameFrom, SDL_Rect* current);

    std::type_info const& GetComponentType() const override { return typeid(MrHotDogAIComponent); }
private:
    enum class State
    {
        CHASING,
        CLIMBING
    };

    State m_State = State::CHASING;
    float m_Speed = 100.0f;

    dae::GameObject* m_gameObject;

    std::vector<std::unique_ptr<SDL_Rect>> m_path; // Smart pointer for path to ensure memory safety

    std::vector<std::unique_ptr<SDL_Rect>> m_gridCells; // Smart pointer for grid cells

    glm::vec2 m_cellSize;
    glm::vec2 m_minCoords;
    glm::vec2 m_maxCoords;
    int m_numCellsX;
    int m_numCellsY;

    SDL_Rect* m_startNode;
    SDL_Rect* m_goalNode;
    
    // Helper functions for calculating the path to Peter and checking if the enemy is near a ladder
    std::vector<SDL_Rect*> CalculatePathToPeter(const glm::vec3& position);
    //bool IsNearLadder();
};

