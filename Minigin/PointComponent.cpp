#include "PointComponent.h"
#include "GameEvent.h" 

namespace dae
{
    PointComponent::PointComponent() : m_Score()
    {
    }

    void PointComponent::SetScore(int score)
    {
        m_Score = score;
        Notify(GameEvent::ScoreUpdated);
        if (m_Score >= 500)
        {
            Notify(GameEvent::ScoredWinningpoints);
        }
    }

    void PointComponent::Update(float /*deltaTime*/)
    {
        
    }

    const char* PointComponent::GetComponentType() const
    {
        return "PointComponent";
    }
}
