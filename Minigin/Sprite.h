#pragma once
#include "Texture2D.h"
#include <vector>
#include <map>
#include <string>
#include <glm/vec2.hpp>

namespace dae
{
    class Sprite
    {
    public:
        Sprite(const Texture2D* texturePtr, int pixelsPerUnit, int rowCount,
            int colCount, const std::map<std::string, std::vector<glm::ivec2>>& animations);

        const std::vector<glm::ivec2>& GetAnimation(const std::string& name) const;
        const Texture2D& GetTexture() const;

    private:
        const Texture2D* m_texturePtr;
        int m_pixelsPerUnit;
        glm::ivec2 m_cellSize;
        std::map<std::string, std::vector<glm::ivec2>> m_animations;
    };
}