#include "SpriteRenderer.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Renderer.h"

dae::SpriteRenderer::SpriteRenderer(dae::GameObject* gameObject, const Sprite* sprite, glm::ivec2 drawCell) :
    m_gameObject(gameObject),m_drawCell(drawCell)
{
    SetSprite(sprite);
}

void dae::SpriteRenderer::SetDrawCell(glm::ivec2 drawCell)
{
    m_drawCell = drawCell;
}

void dae::SpriteRenderer::SetSprite(const Sprite* spritePtr)
{
	m_spritePtr = spritePtr;

    if (m_spritePtr)
    {
        // Retrieve the width and height of the texture
        const auto size = m_spritePtr->GetTexture().GetSize();
        m_width = static_cast<float>(size.x);
        m_height = static_cast<float>(size.y);
    }
}

void dae::SpriteRenderer::Update()
{
}

const dae::Sprite* dae::SpriteRenderer::GetSprite() const
{
	return m_spritePtr;
}

void dae::SpriteRenderer::SetDimensions(float width, float height)
{
    m_width = width;
    m_height = height;
}

void dae::SpriteRenderer::Setflip(bool flipx, bool flipy) 
{
    m_flipX = flipx;
    m_flipY = flipy;
}

void dae::SpriteRenderer::Render() const
{
    if (m_spritePtr == nullptr)
        return;

    const glm::vec2& pos = m_gameObject->GetWorldPosition();

    glm::vec2 MidlePoint = pos;
    MidlePoint.x -= m_width / 2.0f;
    MidlePoint.y -= m_height / 2.0f;


    const glm::ivec2& cellSize = m_spritePtr->cellSize;

    Renderer::GetInstance().RenderTexture(m_spritePtr->GetTexture(), // Passing texture pointer
        MidlePoint,                         // Position
        m_drawCell,                // Source location
        cellSize,                    // Cell size
        m_width,         // Width (for scaling)
        m_height,        // Height (for scaling)
        m_flipX,                     // FlipX
        m_flipY                      // FlipY
    );

}