#include "Sprite.h"

#include <stdexcept>

namespace dae
{
    Sprite::Sprite(const Texture2D* texturePtr, int pixelsPerUnit, int rowCount,
        int colCount, const std::map<std::string, std::vector<glm::ivec2>>& animations)
        : m_texturePtr(texturePtr), m_pixelsPerUnit(pixelsPerUnit), m_cellSize(texturePtr->GetSize().x / colCount, texturePtr->GetSize().y / rowCount), m_animations(animations)
    {
    }

    const std::vector<glm::ivec2>& Sprite::GetAnimation(const std::string& name) const
    {
        auto it = m_animations.find(name);
        if (it != m_animations.end())
            return it->second;
        else
            throw std::runtime_error("Animation not found: " + name);
    }

    const Texture2D& Sprite::GetTexture() const
    {
        return *m_texturePtr;
    }
}
