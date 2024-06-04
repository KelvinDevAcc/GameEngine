// made with the help of julian rijken
#pragma once
#ifndef DAE_MESSAGE_QUEUE_H
#define DAE_MESSAGE_QUEUE_H

#include <any>
#include <functional>
#include <queue>
#include <unordered_map>
#include <variant>

namespace dae {

    enum class PlaySoundMessageType {
        deathSound,
        LevelIntro,
        Main,
        win,
        pepper,
        steppingOnBurger,
        bugerMenu,
        menuSelect,
        menuMove
    };

    enum class PointsMessageType {
        addScore,
        damage
    };

    struct Message
    {
        std::variant<PlaySoundMessageType, PointsMessageType> type;
        std::vector<std::any> arguments;
    };


    class EventQueue {
    public:
        static void Broadcast(const Message& message) {
            messages.push(message);
        }

        template<typename T>
        static void AddListener(auto eventType, T* object,
            void (T::* memberFunction)(const Message&))
        {
            listeners.insert({
                eventType,
                {object, [=](const Message& message) {
                    (object->*memberFunction)(message);
                }}
                });
        }

        template<typename T>
        static void RemoveListener(T* object)
        {
            for (auto it = listeners.begin(); it != listeners.end();) {
                if (it->second.first == object) {
                    it = listeners.erase(it);
                }
                else {
                    ++it;
                }
            }
        }

        static void Process()
        {
            while (!EventQueue::messages.empty())
            {
                Message message = EventQueue::messages.front();
                EventQueue::messages.pop();

                auto range = EventQueue::listeners.equal_range(message.type);
                for (auto it = range.first; it != range.second; ++it) {
                    // Call the listener function with the message
                    const auto& listener = it->second;
                    listener.second(message);
                }

            }
        }

    private:
        using Listener = std::pair<void*, std::function<void(const Message&)>>;
        static inline std::unordered_multimap<std::variant<PlaySoundMessageType, PointsMessageType>, Listener> listeners{};
        static inline std::queue<Message> messages{};
    };

    
}

#endif  // DAE_MESSAGE_QUEUE_H
