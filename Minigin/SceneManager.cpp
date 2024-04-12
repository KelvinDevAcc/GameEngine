#include "SceneManager.h"

#include <stdexcept>


namespace dae
{
    Scene* SceneManager::CreateScene(const std::string& name)
    {
        auto scene = std::make_unique<Scene>(name);
        m_scenes.push_back(std::move(scene));

        //// If this is the first scene, or if no scene is currently active, make it active
        //if (m_scenes.size() == 1 || m_activeSceneIterator == m_scenes.end())
        //    m_activeSceneIterator = m_scenes.begin();

        return m_scenes.back().get();
    }

    Scene* SceneManager::GetActiveScene() const
    {
        return m_activeSceneIterator->get();
    }

    void SceneManager::SetActiveScene(const std::string& name)
    {
        for (auto it = m_scenes.begin(); it != m_scenes.end(); ++it)
        {
            if ((*it)->GetName() == name)
            {
                m_activeSceneIterator = it;
                return;
            }
        }
        // Throw an exception if the scene with the specified name is not found
        throw std::runtime_error("Scene not found: " + name);
    }
    void SceneManager::GoToNextScene()
    {
        // Advance to the next scene
        ++m_activeSceneIterator;
        if (m_activeSceneIterator == m_scenes.end()) // If it reaches the end, loop back to the beginning
            m_activeSceneIterator = m_scenes.begin();
    }

    void SceneManager::Update() const
    {
        if (m_activeSceneIterator != m_scenes.end())
        {
            (*m_activeSceneIterator)->Update();
        }
    }

    void SceneManager::Render() const
    {
        if (m_activeSceneIterator != m_scenes.end())
        {
            (*m_activeSceneIterator)->Render();
        }
    }
}
