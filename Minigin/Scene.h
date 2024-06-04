#pragma once
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"
#include "sound_system.h"

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

        const std::string& GetName() const { return m_name; }
        const std::vector<std::unique_ptr<GameObject>>& GetObjects() const;

        explicit Scene(std::string name);
        ~Scene() = default;
        Scene(const Scene& other) = delete;
        Scene(Scene&& other) = delete;
        Scene& operator=(const Scene& other) = delete;
        Scene& operator=(Scene&& other) = delete;

        void SetBackgroundMusic(const std::string& musicFilePath);
        void SetBackgroundMusic(int musicid);
        void PlayBackgroundMusic();
        void StopBackgroundMusic();
        sound_id GetBackgroundMusicID() const { return  m_backgroundMusicID; }

    private:

        std::string m_name;
        std::vector<std::unique_ptr<GameObject>> m_objects{};
        sound_id m_backgroundMusicID{ 0 };
    };
}
