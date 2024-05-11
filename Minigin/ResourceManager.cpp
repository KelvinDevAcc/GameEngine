#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::unique_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_unique<Texture2D>(texture);
}

std::unique_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_unique<Font>(m_dataPath + file, size);
}

std::unique_ptr<Sprite> dae::ResourceManager::LoadSpriteSheet(const std::string& file, int frameWidth, int frameHeight, int frameCount) const
{
	const auto fullPath = m_dataPath + file;
	auto spriteSheet = std::make_unique<Sprite>(fullPath, frameWidth, frameHeight, frameCount);
	return spriteSheet;
}