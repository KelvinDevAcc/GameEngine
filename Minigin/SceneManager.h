#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Singleton.h"
#include "Scene.h"

namespace dae
{
    class SceneManager final : public Singleton<SceneManager>
    {
    public:
        Scene* CreateScene(const std::string& name);
        Scene* GetActiveScene() const;

        void Update(float deltaTime) const;
        void Render() const;

    private:
        std::vector<std::unique_ptr<Scene>> m_scenes{};
        int m_activeSceneIndex = 0; // Index to keep track of the active scene
    };
}
