#include "InputManager.h"

#include <SDL.h>

#include "backends/imgui_impl_sdl2.h"

using namespace dae;

GameController InputManager::m_gameController;
std::unordered_map<std::pair<unsigned int, KeyState>, std::unique_ptr<Command>> InputManager::m_controllerBindings;
std::unordered_map<std::pair<unsigned int, KeyState>, std::unique_ptr<Command>> InputManager::m_keyboardBindings;

const Uint8* InputManager::m_PreviousState = SDL_GetKeyboardState(nullptr);
const Uint8* InputManager::m_CurrentState = SDL_GetKeyboardState(nullptr);

bool InputManager::ProcessInput()
{
    m_gameController.UpdateState();

    m_PreviousState = m_CurrentState;
    // Update the current state
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

void InputManager::BindCommand(unsigned int button, KeyState state, std::unique_ptr<Command> command, InputType type)
{
    auto& bindings = (type == InputType::Controller) ? m_controllerBindings : m_keyboardBindings;
    bindings[{button, state}] = std::move(command);
}

void InputManager::UnbindCommand(unsigned int button, KeyState state, InputType type)
{
    auto& bindings = (type == InputType::Controller) ? m_controllerBindings : m_keyboardBindings;
    bindings.erase({ button, state });
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

void InputManager::HandleControllerInput()
{
    for (const auto& binding : m_controllerBindings)
    {
        const auto button = binding.first.first;

        switch (const auto state = binding.first.second)
        {
        case KeyState::Down:
            if (m_gameController.IsButtonDown(button))
            {
                binding.second->Execute();
            }
            break;
        case KeyState::Up:
            if (m_gameController.IsButtonUp(button))
            {
                binding.second->Execute();
            }
            break;
        case KeyState::Pressed:
            if (m_gameController.IsButtonPressed(button))
            {
                binding.second->Execute();
            }
            break;
        }
    }
}
