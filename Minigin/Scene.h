#pragma once
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"

namespace dae
{

    class Scene final
    {
    public:
        void Add(std::unique_ptr<GameObject> object);
        void Remove(GameObject* object);
        void RemoveAll();

        void Update() const;
        void Render() const;

        const std::vector<std::unique_ptr<GameObject>>& GetObjects() const;

        explicit Scene(std::string name);
        ~Scene();
        Scene(const Scene& other) = delete;
        Scene(Scene&& other) = delete;
        Scene& operator=(const Scene& other) = delete;
        Scene& operator=(Scene&& other) = delete;

    private:

        std::string m_name;
        std::vector<std::unique_ptr<GameObject>> m_objects{};

        static unsigned int m_idCounter;
    };
}