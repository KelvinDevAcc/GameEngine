#include "RotatorComponent.h"


dae::RotatorComponent::RotatorComponent(float rotationSpeed, float centerX, float centerY, float radius)
    : m_RotationSpeed(rotationSpeed), m_CurrentRotation(0.0f), m_CenterX(centerX), m_CenterY(centerY), m_Radius(radius)
{}

void dae::RotatorComponent::Update(float deltaTime)
{
    // Update rotation based on rotation speed and delta time
    m_CurrentRotation += m_RotationSpeed * deltaTime;

    // Apply rotation around the specified center point
    if (m_pGameObject)
    {
        // Calculate the new positions after rotation
        float newX = m_CenterX + m_Radius * std::cos(m_CurrentRotation);
        float newY = m_CenterY + m_Radius * std::sin(m_CurrentRotation);

        // Set the new position of the object
        m_pGameObject->SetLocalPosition(glm::vec3(newX, newY, 0.0f));
    }
}