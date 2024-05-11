#pragma once
#include <SDL.h>

#include "RenderComponent.h"
#include "Singleton.h"

namespace dae
{
	class Texture2D;

	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, float pos_x, float y, float width, float height, float rotation_angle) const;
		void RenderTexture(const Texture2D& texture, float x, float y, const glm::vec2& cellSize, int pixelsPerUnit) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, float rotation_angle, const SDL_Rect* srcRect, SDL_RendererFlip flip) const;


		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

