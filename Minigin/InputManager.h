#pragma once

#include <unordered_map>
#include <memory>
#include <SDL.h>

#include "Command.h"
#include "Singleton.h"
#include "GameController.h"

enum class KeyState
{
    Down,
    Up,
    Pressed
};

enum class InputType
{
    Controller,
    Keyboard
};

namespace dae
{
    class InputManager final : public Singleton<InputManager>
    {
    public:
        static bool ProcessInput();
        static bool IsDownThisFrame(SDL_Scancode button);
        static bool IsUpThisFrame(SDL_Scancode button);
        static bool IsPressed(SDL_Scancode button);

        static void BindCommand(unsigned int button, KeyState state, std::unique_ptr<Command> command, InputType type);
        static void UnbindCommand(unsigned int button, KeyState state, InputType type);

    private:
        static void handleKeyinput();
        static void handleKeyinput(SDL_Scancode keyCode, KeyState state);
        static void handlecontrollerinput();

        static GameController m_gameController;
        static std::unordered_map<std::pair<unsigned int, KeyState>, std::unique_ptr<Command>> m_controllerBindings;
        static std::unordered_map<std::pair<unsigned int, KeyState>, std::unique_ptr<Command>> m_keyboardBindings;
        static std::unordered_map<unsigned int, bool> m_KeysPressed;

        static const Uint8* m_PreviousState;
        static const Uint8* m_CurrentState;
    };
}

template <>
struct std::hash<std::pair<unsigned int, KeyState>>
{
    size_t operator()(const std::pair<unsigned int, KeyState>& p) const noexcept
    {
        return std::hash<unsigned int>()(p.first) ^ std::hash<int>()(static_cast<int>(p.second));
    }
};
