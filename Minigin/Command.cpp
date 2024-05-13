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
    message.arguments.emplace_back(50.f); // volume

    dae::EventQueue::Broadcast(message);
}