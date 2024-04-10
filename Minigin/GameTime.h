#pragma once

#include <chrono>

class GameTime
{
public:
    GameTime() : m_LastTime(std::chrono::high_resolution_clock::now()), m_DeltaTime(0)
    {
    }

    void Update()
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
        m_LastTime = currentTime;
    }

    float GetDeltaTime() const { return m_DeltaTime; }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime;
    float m_DeltaTime;
};