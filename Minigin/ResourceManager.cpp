#include "ResourceManager.h"
#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Renderer.h"

std::string dae::ResourceManager::m_dataPath;

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error("Failed to initialize font support: " + std::string(SDL_GetError()));
	}
}


dae::Font* dae::ResourceManager::LoadFont(const std::string& name, const std::string& file, unsigned int size)
{
	auto fullPath = m_dataPath + file;
	auto font = std::make_unique<Font>(fullPath, size);
	auto [it, success] = g_FontUPtrMap.emplace(name, std::move(font));
	if (!success)
	{
		std::cerr << "Error: Font '" << name << "' already loaded.\n";
		return nullptr;
	}
	return it->second.get();
}

dae::Texture2D* dae::ResourceManager::LoadTexture(const std::string& fileName)
{
	const auto& fullPath = m_dataPath + fileName;
	SDL_Texture* texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());

	if (texture == nullptr)
		std::cerr << "Error: Failed to load texture '" << fileName << "': " << IMG_GetError() << '\n';


	return g_LoadedTextureUPtrs.emplace_back(std::make_unique<Texture2D>(texture)).get();
}

dae::Sprite* dae::ResourceManager::LoadSprite(const std::string& name, const std::string& fileName, int rowCount, int colCount, const std::map<std::string, SpriteAnimation>& animations)
{
	return g_SpriteUPtrMap.emplace(name,std::make_unique<Sprite>(LoadTexture(m_dataPath + fileName), rowCount, colCount, animations)).first->second.get();
}

dae::Sprite* dae::ResourceManager::GetSprite(const std::string& name)
{
	if (g_SpriteUPtrMap.contains(name))
		return g_SpriteUPtrMap.at(name).get();

	std::cerr << "Error: Sprite '" << name << "' not found.\n";
	return nullptr;
}

dae::Font* dae::ResourceManager::GetFont(const std::string& name)
{
	if (g_FontUPtrMap.contains(name))
		return g_FontUPtrMap.at(name).get();

	std::cerr << "Error: Font '" << name << "' not found.\n";
	return nullptr;
}
