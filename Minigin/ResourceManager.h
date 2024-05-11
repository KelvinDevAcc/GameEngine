#pragma once
#include <string>
#include <memory>
#include "Singleton.h"
#include "Sprite.h"

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::unique_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::unique_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
		std::unique_ptr<Sprite> LoadSpriteSheet(const std::string& file, int frameWidth, int frameHeight, int frameCount) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
	};
}
