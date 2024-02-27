#include "SceneManager.h"
#include <stdexcept>

#include "RenderComponent.h"
#include "Scene.h"

namespace dae
{
    void SceneManager::Update(float deltaTime) const
    {
        for (auto& scene : m_scenes)
        {
            scene->Update(deltaTime);
        }
    }

    void SceneManager::Render() const
    {
        for (const auto& scene : m_scenes)
        {
            scene->Render();
        }
    }

    Scene& SceneManager::CreateScene(const std::string& name)
    {
        const auto& scene = std::shared_ptr<Scene>(new Scene(name));
        m_scenes.push_back(scene);
        return *scene;
    }

    Scene& SceneManager::GetActiveScene() const
    {
        if (m_activeSceneIndex >= 0 && m_activeSceneIndex < static_cast<int>(m_scenes.size()))
        {
            return *m_scenes[m_activeSceneIndex];
        }
        else
        {
            // Handle the case where the active scene index is out of range
            throw std::out_of_range("No active scene available or active scene index out of range");
        }
    }
}
