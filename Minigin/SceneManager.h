#pragma once
#include <vector>
#include <string>
#include <memory>

#include "GameObject.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetActiveScene() const;

		void Update(float deltaTime) const;
		void Render() const;

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		int m_activeSceneIndex = 0; // Index to keep track of the active scene
	};
}