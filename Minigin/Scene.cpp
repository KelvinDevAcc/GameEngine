#include "Scene.h"
#include <string>

namespace dae
{
    unsigned int Scene::m_idCounter = 0;

    Scene::Scene(std::string name) : m_name(std::move(name)) {}

    Scene::~Scene() = default;

    void Scene::Add(std::unique_ptr<GameObject> object)
    {
        m_objects.emplace_back(std::move(object));
    }

    void Scene::Remove(GameObject* object)
    {
        auto it = std::remove_if(m_objects.begin(), m_objects.end(),
            [object](const auto& ptr) { return ptr.get() == object; });

        if (it != m_objects.end())
        {
            m_objects.erase(it, m_objects.end());
        }
    }

    void Scene::RemoveAll()
    {
        m_objects.clear();
    }

    void Scene::Update() const
    {
        for (const auto& object : m_objects)
        {
            object->Update();
        }
    }

    void Scene::Render() const
    {
        for (const auto& object : m_objects)
        {
            object->Render();
        }
    }

    const std::vector<std::unique_ptr<GameObject>>& Scene::GetObjects() const
    {
        return m_objects;
    }
}