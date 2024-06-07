#include "InputManager.h"

#include <SDL.h>

#include "backends/imgui_impl_sdl2.h"

using namespace dae;

std::array<GameController, 4> InputManager::m_gameControllers = { GameController(0), GameController(1), GameController(2), GameController(3) };
std::array<std::unordered_map<std::pair<unsigned int, KeyState>, std::unique_ptr<Command>>, 4> InputManager::m_controllerBindings;
std::unordered_map<std::pair<unsigned int, KeyState>, std::unique_ptr<Command>> InputManager::m_keyboardBindings;

const Uint8* InputManager::m_PreviousState = SDL_GetKeyboardState(nullptr);
const Uint8* InputManager::m_CurrentState = SDL_GetKeyboardState(nullptr);

bool InputManager::ProcessInput()
{
    for (auto& controller : m_gameControllers)
    {
        controller.UpdateState();
    }

    m_PreviousState = m_CurrentState;
    m_CurrentState = SDL_GetKeyboardState(nullptr);

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            return false;
        case SDL_KEYDOWN:
            HandleKeyInput(e.key.keysym.scancode, KeyState::Down);
            break;
        case SDL_KEYUP:
            HandleKeyInput(e.key.keysym.scancode, KeyState::Up);
            break;
        default:
            break;
        }
        ImGui_ImplSDL2_ProcessEvent(&e);
    }

    HandleKeyInput();
    HandleControllerInput();

    return true;
}



bool InputManager::IsDownThisFrame(SDL_Scancode button)
{
    return m_CurrentState[button] && !m_PreviousState[button];
}

bool InputManager::IsUpThisFrame(SDL_Scancode button)
{
    return !m_CurrentState[button] && m_PreviousState[button];
}

bool InputManager::IsPressed(SDL_Scancode button) 
{
    return m_CurrentState[button];
}

void InputManager::BindCommand(unsigned int button, KeyState state, std::unique_ptr<Command> command, InputType type, int controllerIndex)
{
    if (type == InputType::Controller)
    {
        if (controllerIndex < m_controllerBindings.size())
        {
            m_controllerBindings[controllerIndex][{button, state}] = std::move(command);
        }
    }
    else
    {
        m_keyboardBindings[{button, state}] = std::move(command);
    }
}

void InputManager::UnbindCommand(unsigned int button, KeyState state, InputType type, int controllerIndex)
{
    if (type == InputType::Controller)
    {
        if (controllerIndex < m_controllerBindings.size())
        {
            m_controllerBindings[controllerIndex].erase({ button, state });
        }
    }
    else
    {
        m_keyboardBindings.erase({ button, state });
    }
}


void InputManager::HandleKeyInput()
{
    // Process keyboard bindings
    for (const auto& binding : m_keyboardBindings)
    {
        const auto keyCode = static_cast<SDL_Scancode>(binding.first.first);

        if (IsPressed(keyCode) && binding.first.second == KeyState::Pressed)
        {
            binding.second->Execute();
        }
    }
}



void InputManager::HandleKeyInput(SDL_Scancode keyCode, KeyState state)
{
    for (const auto& binding : m_keyboardBindings)
    {
        if (static_cast<SDL_Scancode>(binding.first.first) == keyCode && binding.first.second == state)
        {
            binding.second->Execute();
            break;
        }
    }
}

void InputManager::HandleControllerInput() {
    for (int i = 0; i < m_controllerBindings.size(); ++i) {
        if (m_controllerBindings[i].empty() || !m_gameControllers[i].IsConnected()) {
            continue; // Skip this iteration if no bindings or controller not connected
        }

        for (const auto& binding : m_controllerBindings[i]) {
            const auto button = binding.first.first;
            const auto state = binding.first.second;
            const auto& command = binding.second;

            switch (state) {
            case KeyState::Down:
                if (m_gameControllers[i].IsButtonDown(button)) {
                    command->Execute();
                }
                break;
            case KeyState::Up:
                if (m_gameControllers[i].IsButtonUp(button)) {
                    command->Execute();
                }
                break;
            case KeyState::Pressed:
                if (m_gameControllers[i].IsButtonPressed(button)) {
                    command->Execute();
                }
                break;
            }
        }
    }
}


