#include "PointsDisplayComponent.h"

#include <SDL_ttf.h>
#include <stdexcept>

namespace dae
{
    PointsDisplayComponent::PointsDisplayComponent(std::unique_ptr<Font> font)
        : m_pointComponent(nullptr), m_font(std::move(font)), m_textTexture(nullptr)
    {
    }

    void PointsDisplayComponent::Update(float /*deltaTime*/)
    {
        // Update the text to display current score
        if (m_pointComponent)
        {
	        const std::string text = "Points: " + std::to_string(m_pointComponent->GetScore());
            RenderText(text);
        }
    }

    void PointsDisplayComponent::Render() const
    {
        if (m_textTexture != nullptr)
        {
            const auto& pos = m_transform.GetPosition();
            const float textureWidth = static_cast<float>(m_textTexture->GetSize().x);
            const float posX = pos.x - textureWidth / 2.0f;

            Renderer::GetInstance().RenderTexture(*m_textTexture, posX, pos.y);
        }
    }
    void PointsDisplayComponent::SetPosition(float x, float y)
    {
        m_transform.SetPosition(glm::vec3(x, y, 0.0f));
    }
    void PointsDisplayComponent::AttachToPointComponent(PointComponent* pointComponent)
    {
        m_pointComponent = pointComponent;
    }
    void PointsDisplayComponent::RenderText(const std::string& text)
    {
        const SDL_Color color = { 255, 255, 255, 255 }; // White color
        const auto surf = TTF_RenderText_Blended(m_font->GetFont(), text.c_str(), color);
        if (surf == nullptr)
        {
            throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
        }

        if (m_textTexture != nullptr)
        {
            SDL_DestroyTexture(m_textTexture->GetSDLTexture());
            m_textTexture = nullptr; // Reset the unique_ptr
        }

        auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
        if (texture == nullptr)
        {
            throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
        }

        SDL_FreeSurface(surf);
        m_textTexture = std::make_unique<Texture2D>(texture);
    }
    void PointsDisplayComponent::Update()
    {
    }
}
