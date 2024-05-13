//made with help of julian
#pragma once
#include <filesystem>
#include <string>
#include <memory>

#include "Font.h"
#include "Singleton.h"
#include "Sprite.h"

#include "Texture2D.h"

namespace dae
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		static void Init(const std::string& data);

		static Font* LoadFont(const std::string& assetName, const std::string& file, unsigned int size);


		static Texture2D* LoadTexture(const std::string& filePath);
		static Sprite* LoadSprite(const std::string& assetName, const std::string& fileName, int rowCount = 1, int colCount = 1,const std::map<std::string, SpriteAnimation>& animations = {});

		static Sprite* GetSprite(const std::string& name);
		static Font* GetFont(const std::string& name);

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		static std::string m_dataPath;

		inline static std::map<std::string, std::unique_ptr<Font>> g_FontUPtrMap{};
		inline static std::map<std::string, std::unique_ptr<Sprite>> g_SpriteUPtrMap{};
		inline static std::vector<std::unique_ptr<Texture2D>> g_LoadedTextureUPtrs{};
	};
}
