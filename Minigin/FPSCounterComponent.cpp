#include "FPSCounterComponent.h"
#include <iostream>

    void dae::FPSCounterComponent::Update()
    {
        // Update frame count and elapsed time using stored delta time
        m_frameCount++;
        m_elapsedTime += deltaTime;

        // If one second has passed, calculate FPS
        if (m_elapsedTime >= 1.0f)
        {
            m_fps = static_cast<float>(m_frameCount) / m_elapsedTime;

            // Reset frame count and elapsed time
            m_frameCount = 0;
            m_elapsedTime = 0.0f;
        }
    }

    float dae::FPSCounterComponent::GetFPS() const
    {
        return m_fps;
    }


