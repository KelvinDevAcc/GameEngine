#include "MrHotDogAIComponent.h"

#include <iostream>
#include <queue>
#include <unordered_set>

#include "GameObject.h"
#include "SceneData.h"
#include "SceneHelpers.h"


MrHotDogAIComponent::MrHotDogAIComponent(dae::GameObject* owner)
{
	m_gameObject = owner;

    m_startNode = nullptr;
    m_goalNode = nullptr;
	m_cellSize = SceneHelpers::GetCellSize();

	// Get the minimum and maximum coordinates of the map
	m_minCoords = SceneHelpers::GetMinCoordinates();
	m_minCoords.x -= m_cellSize.x / 2;
	m_minCoords.y += m_cellSize.y / 2;
	m_maxCoords = SceneHelpers::GetMaxCoordinates();
	m_maxCoords.x += m_cellSize.x;
	m_maxCoords.y += m_cellSize.y;

	m_numCellsX = static_cast<int>((m_maxCoords.x - m_minCoords.x) / m_cellSize.x);
	m_numCellsY = static_cast<int>((m_maxCoords.y - m_minCoords.y) / m_cellSize.y);

	// Draw the grid
	for (int i = 0; i < m_numCellsY; ++i)
	{
		for (int j = 0; j < m_numCellsX; ++j)
		{
			// Calculate the top-left corner of the cell
			const float x = m_minCoords.x + static_cast<int>(j) * (m_cellSize.x);
			const float y = m_minCoords.y + static_cast<int>(i) * (m_cellSize.y);

			// Create the SDL_Rect for the cell
            auto cellRect = std::make_unique<SDL_Rect>();
            cellRect->x = static_cast<int>(x);
            cellRect->y = static_cast<int>(y);
            cellRect->w = static_cast<int>(m_cellSize.x);
            cellRect->h = static_cast<int>(m_cellSize.y);

            m_gridCells.push_back(std::move(cellRect));
		}
	}
}

void MrHotDogAIComponent::Update()
{
    const auto position = m_gameObject->GetWorldPosition();

    // Calculate the shortest path to Peter using a pathfinding algorithm
    const auto pathToPeter = CalculatePathToPeter(position);

    // Convert raw pointers to unique_ptr and store them in m_path
    for (SDL_Rect* rectPtr : pathToPeter) {
        m_path.push_back(std::make_unique<SDL_Rect>(*rectPtr));
    }

    // Update the enemy's state based on the current state
    switch (m_State)
    {
    case State::CHASING:
    {
        if (!m_path.empty())
        {
            const auto& targetPosition = m_path.front();

            // Move towards the target position
            auto direction = glm::vec3(targetPosition->x, targetPosition->y, position.z) - position;
            direction.y = 0; // Ignore the y component of the direction for now
            direction = glm::normalize(direction);

            m_gameObject->SetLocalPosition(position + direction * m_Speed * dae::GameTime::GetDeltaTime());

            // Check if the enemy reached the target position
            const float distanceToTarget = glm::length(glm::vec3(targetPosition->x, targetPosition->y, position.z) - position);
            if (distanceToTarget < m_Speed * dae::GameTime::GetDeltaTime())
            {
                // Remove the current target position from the path
                m_path.erase(m_path.begin());
            }
        }

        //// Implement chasing behavior on the floor
        if (dae::SceneData::GetInstance().IsOnFloor(*m_gameObject))
        {
            // If the enemy is on a floor, they will continue chasing Peter
            // DisplayPath(path);
        }
        else if (dae::SceneData::GetInstance().IsOnLadder(*m_gameObject))
        {
            // If the enemy is on a ladder, they will switch to the CLIMBING state
            m_State = State::CLIMBING;
        }
        break;
    }
    case State::CLIMBING:
        // Implement climbing behavior
        // For example, you could make the enemy move up or down a ladder
        if (!dae::SceneData::GetInstance().IsOnLadder(*m_gameObject))
        {
            // If the enemy has reached the top or bottom of the ladder,
            // they will switch to the CHASING state and continue moving towards Peter's position
            m_State = State::CHASING;
        }
        else
        {
            // Climbing logic: Move up or down the ladder
            // Placeholder code, replace with actual climbing logic
            const glm::vec3 ladderDirection = glm::vec3(0, -1, 0); // Assume moving up for now
            m_gameObject->SetLocalPosition(position + ladderDirection * m_Speed * dae::GameTime::GetDeltaTime());
        }
        break;
    }
}

void MrHotDogAIComponent::Render() const
{
    if (!m_gridCells.empty())
    {
        for (const auto& cellRect : m_gridCells)
        {
            dae::Renderer::GetInstance().RenderRect(*cellRect, SDL_Color{ 255, 255, 255, 255 }, false); // White color for grid cells, not filled
        }
    }
    

    if (!m_path.empty())
    {
        // Draw rectangles along the path
        for (const auto& rectPtr : m_path)
        {
            // Render the rectangle
            dae::Renderer::GetInstance().RenderRect(*rectPtr, SDL_Color{ 255, 0, 0, 255 }, true); // Red color for rectangles
        }
    }


    //if (m_startNode && m_goalNode)
    //{
    //    dae::Renderer::GetInstance().RenderRect(*m_startNode, SDL_Color{ 255, 0, 0, 255 }, true); // Green color for path lines
    //    dae::Renderer::GetInstance().RenderRect(*m_goalNode, SDL_Color{ 0, 0, 255, 255 }, true); // Green color for path lines
    //}
}



std::vector<SDL_Rect*> MrHotDogAIComponent::CalculatePathToPeter(const glm::vec3& position)
{
    m_path.clear();
    const int startX = static_cast<int>((position.x - m_minCoords.x) / m_cellSize.x);
    const int startY = static_cast<int>((position.y - m_minCoords.y) / m_cellSize.y);

    m_startNode = m_gridCells[startY * m_numCellsX + startX].get();

    // Find the closest player
    const auto players = dae::SceneData::GetInstance().GetPlayers();
    glm::vec3 closestPlayerPosition = glm::vec3(0, 0, 0);
    float closestDistance = std::numeric_limits<float>::max();

    for (const auto& player : players)
    {
        glm::vec3 playerPosition = player->GetWorldPosition();
        float distance = glm::distance(position, playerPosition);
        if (distance < closestDistance)
        {
            closestDistance = distance;
            closestPlayerPosition = playerPosition;
        }
    }

    const int goalX = static_cast<int>((closestPlayerPosition.x - m_minCoords.x) / m_cellSize.x);
    const int goalY = static_cast<int>((closestPlayerPosition.y - m_minCoords.y) / m_cellSize.y);

    m_goalNode = m_gridCells[goalY * m_numCellsX + goalX].get();

    std::vector<SDL_Rect*> path;
    std::unordered_set<SDL_Rect*> openSet;
    std::unordered_set<SDL_Rect*> closedSet;
    std::unordered_map<SDL_Rect*, SDL_Rect*> cameFrom;
    std::unordered_map<SDL_Rect*, float> gScore;
    std::unordered_map<SDL_Rect*, float> fScore;

    // Initialize scores
    for (auto& node : m_gridCells) {
        gScore[node.get()] = std::numeric_limits<float>::infinity();
        fScore[node.get()] = std::numeric_limits<float>::infinity();
    }

    gScore[m_startNode] = 0;
    fScore[m_startNode] = GetHeuristicCost(m_startNode, m_goalNode);

    openSet.insert(m_startNode);

    while (!openSet.empty()) {
        auto currentNode = *std::ranges::min_element(openSet,
                                                     [&](SDL_Rect* a, SDL_Rect* b) { return fScore[a] < fScore[b]; });

        if (currentNode == m_goalNode) {
            path = ReconstructPath(cameFrom, m_goalNode);
            break;
        }

        openSet.erase(currentNode);
        closedSet.insert(currentNode);

        for (auto neighbor : GetNeighbors(currentNode)) {
            if (closedSet.contains(neighbor))
                continue; // Ignore the neighbor which is already evaluated

            float tentativeGScore = gScore[currentNode] + GetCost(currentNode, neighbor);

            if (!openSet.contains(neighbor)) // Discover a new node
                openSet.insert(neighbor);
            else if (tentativeGScore >= gScore[neighbor])
                continue; // This is not a better path

            // This path is the best until now. Record it!
            cameFrom[neighbor] = currentNode;
            gScore[neighbor] = tentativeGScore;
            fScore[neighbor] = gScore[neighbor] + GetHeuristicCost(neighbor, m_goalNode);
        }
    }

    return path;
}

std::vector<SDL_Rect*> MrHotDogAIComponent::GetNeighbors(SDL_Rect* pNode)
{
    std::vector<SDL_Rect*> neighbors;

    // Define offsets for neighboring cells (north, south, east, west)
    int offsets[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // {row_offset, col_offset}

    // Get grid coordinates of pNode
    const auto pNodeIterator = std::ranges::find_if(m_gridCells,
                                                    [pNode](const std::unique_ptr<SDL_Rect>& rect) {
	                                                    return rect.get() == pNode;
                                                    });
    if (pNodeIterator != m_gridCells.end()) {
        const int pNodeIndex = static_cast<int>(std::distance(m_gridCells.begin(), pNodeIterator));
        const int row = pNodeIndex / m_numCellsX;
        const int col = pNodeIndex % m_numCellsX;

        // Iterate over offsets to find neighboring cells
        for (int i = 0; i < 4; ++i) {
            const int newRow = row + offsets[i][0];
            const int newCol = col + offsets[i][1];

            // Check if the neighboring cell is within the bounds of the grid
            if (newRow >= 0 && newRow < m_numCellsY && newCol >= 0 && newCol < m_numCellsX) {
                // Calculate index of neighboring cell in m_gridCells
                const int neighborIndex = newRow * m_numCellsX + newCol;
                // Add neighboring cell to neighbors vector
                neighbors.push_back(m_gridCells[neighborIndex].get());
            }
        }
    }


    return neighbors;
}


std::vector<SDL_Rect*> MrHotDogAIComponent::ReconstructPath(const std::unordered_map<SDL_Rect*, SDL_Rect*>& cameFrom, SDL_Rect* current)
{
    std::vector<SDL_Rect*> path;
    while (cameFrom.count(current) > 0) {
        path.push_back(current);
        current = cameFrom.at(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

float MrHotDogAIComponent::GetCost(SDL_Rect* /*pNodeA*/, SDL_Rect* /*pNodeB*/)
{
    // For simplicity, let's assume a constant cost for moving between adjacent cells
    return 1.0f; // Adjust as needed based on your game mechanics
}

float MrHotDogAIComponent::GetHeuristicCost(SDL_Rect* pNodeA, SDL_Rect* pNodeB)
{
    // Calculate Manhattan distance between pNodeA and pNodeB
    int dx = abs(pNodeA->x - pNodeB->x);
    int dy = abs(pNodeA->y - pNodeB->y);
    return static_cast<float>(dx + dy);
}
