#include "Sprite.h"

#include <stdexcept>

#include "ResourceManager.h"

Sprite::Sprite(const std::string& filePath, int frameWidth, int frameHeight, int frameCount)
    : m_texture(nullptr), m_frameWidth(frameWidth), m_frameHeight(frameHeight)
{
    // Load the spritesheet texture
    m_texture = dae::ResourceManager::GetInstance().LoadTexture(filePath);
    if (!m_texture)
    {
        throw std::runtime_error("Failed to load spritesheet texture: " + filePath);
    }

    // Calculate frame positions on the spritesheet
    for (int i = 0; i < frameCount; ++i)
    {
        FrameData frame;
        frame.rect.x = (i % (frameCount / (frameWidth / frameHeight))) * frameWidth;
        frame.rect.y = (i / (frameCount / (frameWidth / frameHeight))) * frameHeight;
        frame.rect.w = frameWidth;
        frame.rect.h = frameHeight;
        m_frames.push_back(frame);
    }
}

Sprite::~Sprite()
{
    if (m_texture)
    {
        m_texture = nullptr;
    }
}

dae::Texture2D* Sprite::GetTexture() const
{
    return m_texture.get();
}

const FrameData& Sprite::GetFrame(int index) const
{
    if (index < 0 || index >= m_frames.size())
    {
        throw std::out_of_range("Frame index out of range");
    }
    return m_frames[index];
}