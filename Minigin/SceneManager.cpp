#include "SceneManager.h"

#include <stdexcept>


namespace dae
{
    Scene* SceneManager::CreateScene(const std::string& name)
    {
        // Creating a new Scene instance using Scene constructor
        auto scene = std::make_unique<Scene>(name);
        m_scenes.push_back(std::move(scene));
        return m_scenes.back().get();
    }

    Scene* SceneManager::GetActiveScene() const
    {
        if (m_activeSceneIndex >= 0 && m_activeSceneIndex < static_cast<int>(m_scenes.size()))
        {
            return m_scenes[m_activeSceneIndex].get(); // Return a raw pointer
        }
        else
        {
            // Handle the case where the active scene index is out of range
            throw std::out_of_range("No active scene available or active scene index out of range");
        }
    }

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
}
