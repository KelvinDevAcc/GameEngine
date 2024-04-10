#include "TextComponent.h"

#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(std::string text, std::unique_ptr<Font> font) 
	: m_needsUpdate(true), m_text(std::move(text)), m_font(std::move(font)), m_textTexture(nullptr)
{ }

void dae::TextComponent::Update()
{
    if (m_needsUpdate)
    {
        const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
        const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
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
        m_needsUpdate = false;
    }
}

void dae::TextComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
        const auto& pos = m_transform.GetPosition();
        const float textureWidth = static_cast<float>(m_textTexture->GetSize().x);
        const float posX = pos.x - textureWidth / 2.0f;

        Renderer::GetInstance().RenderTexture(*m_textTexture, posX, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::SetPosition(float x, float y)
{
    m_transform.SetPosition(glm::vec3(x, y, 0.0f));
}



