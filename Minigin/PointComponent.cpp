#include "PointComponent.h"

namespace dae
{
	PointComponent::PointComponent(const int initalscore): m_Score(initalscore)
	{
	}

    void PointComponent::SetScore(int score)
    {
        m_Score = score;
        Notify(); // Notify observers after updating the score
    }

    void PointComponent::Update(float  /*deltaTime*/)
    {
        // Implement point-related updates here if needed
        // For example, increase score over time, check for scoring conditions, etc.
    }

    const char* PointComponent::GetComponentType() const
    {
        return "PointComponent";
    }
}