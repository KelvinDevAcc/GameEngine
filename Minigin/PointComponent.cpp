#include "PointComponent.h"

namespace dae
{
	PointComponent::PointComponent(const int initalScore): m_Score(initalScore)
	{
	}

    void PointComponent::SetScore(int score)
    {
        m_Score = score;
        Notify(); // Notify observers after updating the score
    }

    void PointComponent::Update()
    {
    }

   
}