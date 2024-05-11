#pragma once
#pragma once

#include <memory>
#include <string>
#include <vector>
#include "SDL.h" // Assuming SDL is used for rendering
#include "Texture2D.h"

struct FrameData
{
    SDL_Rect rect; // Rectangle representing the position and dimensions of the frame on the spritesheet
};

class Sprite
{
public:
    Sprite(const std::string& filePath, int frameWidth, int frameHeight, int frameCount);
    ~Sprite();

    dae::Texture2D* GetTexture() const;
    const FrameData& GetFrame(int index) const;

private:
    std::unique_ptr<dae::Texture2D> m_texture;
    int m_frameWidth;
    int m_frameHeight;
    std::vector<FrameData> m_frames;
};
