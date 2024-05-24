#include "Command.h"
#include "EnventQueue.h"
#include "SceneManager.h"
#include "servicelocator.h"
#include "../BugerTime/Player.h"


MoveCommand::MoveCommand(dae::GameObject* gameObject, float deltaX, float deltaY)
	: m_gameObject(gameObject), m_deltaX(deltaX), m_deltaY(deltaY)
{
}

void MoveCommand::Execute() {
    if (m_gameObject) {
        // Execute the move action
        m_gameObject->GetComponent<game::Player>()->Move(m_deltaX, m_deltaY);
    }
}



DamageCommand::DamageCommand(dae::GameObject* gameObject)
    : m_gameObject(gameObject)
{
}

void DamageCommand::Execute()
{
    // Reduce health by damage amount
    m_gameObject->GetComponent<game::Player>()->Die();
}


ScorePointCommand::ScorePointCommand(dae::GameObject* gameObject)
    : m_gameObject(gameObject)
{
}

void ScorePointCommand::Execute()
{
    // Increase score by score amount
    m_gameObject->GetComponent<game::Player>()->Attack();
}



GoToNextSceneCommand::GoToNextSceneCommand() = default;

void GoToNextSceneCommand::Execute()
{
    auto& sceneManager = dae::SceneManager::GetInstance();
    sceneManager.GoToNextScene();
   
}

PlaySoundCommand::PlaySoundCommand() = default;

void PlaySoundCommand::Execute() {

    dae::Message message;

    message.type = dae::PlaySoundMessageType::deathSound;

    message.arguments.emplace_back(static_cast<sound_id>(1)); // sound ID

    dae::EventQueue::Broadcast(message);
}

MuteCommand::MuteCommand(sound_system* soundSystem)
    : m_soundSystem(soundSystem) {}

void MuteCommand::Execute() {
    if (m_soundSystem) {
        m_soundSystem->mute();
    }
}

IncreaseVolumeCommand::IncreaseVolumeCommand(sound_system* soundSystem)
    : m_soundSystem(soundSystem) {}

void IncreaseVolumeCommand::Execute() {
    if (m_soundSystem) {
        const float currentVolume = m_soundSystem->getVolume();
        m_soundSystem->setVolume(std::min(currentVolume + 10.0f, 128.0f));
    }
}

DecreaseVolumeCommand::DecreaseVolumeCommand(sound_system* soundSystem)
    : m_soundSystem(soundSystem) {}

void DecreaseVolumeCommand::Execute() {
    if (m_soundSystem) {
        const float currentVolume = m_soundSystem->getVolume();
        m_soundSystem->setVolume(std::max(currentVolume - 10.0f, 0.0f));
    }
}



NavigateUpCommand::NavigateUpCommand(dae::MenuComponent* menu) : m_Menu(menu) {}

void NavigateUpCommand::Execute()
{
    if (m_Menu)
    {
        m_Menu->NavigateUp();
    }
}

NavigateDownCommand::NavigateDownCommand(dae::MenuComponent* menu) : m_Menu(menu) {}

void NavigateDownCommand::Execute()
{
    if (m_Menu)
    {
        m_Menu->NavigateDown();
    }
}

SelectOptionCommand::SelectOptionCommand(dae::MenuComponent* menu) : m_Menu(menu) {}

void SelectOptionCommand::Execute()
{
    if (m_Menu)
    {
        m_Menu->SelectOption();
    }
}