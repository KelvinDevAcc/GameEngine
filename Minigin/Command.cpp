#include "Command.h"
#include "EnventQueue.h"
#include "HighScores.h"
#include "SceneData.h"
#include "SceneManager.h"
#include "servicelocator.h"
#include "../BugerTime/Player.h"


MoveCommand::MoveCommand(int playerNumber, float deltaX, float deltaY)
	: m_deltaX(deltaX), m_deltaY(deltaY)
{
	const std::vector<dae::GameObject*> players = dae::SceneData::GetInstance().GetPlayers();

    if (playerNumber >= 0 && playerNumber < static_cast<int>(players.size()))
    {
        m_playernum = playerNumber;
        // Get the selected player using playerNumber
        m_gameObject = players[playerNumber];
    }
}

void MoveCommand::Execute()
{
	if (m_gameObject) {
        // Execute the move action
        m_gameObject->GetComponent<game::Player>()->Move(m_deltaX, m_deltaY);
    }
}



DamageCommand::DamageCommand(int playerNumber)
{
    const std::vector<dae::GameObject*> players = dae::SceneData::GetInstance().GetPlayers();

    if (playerNumber >= 0 && playerNumber < static_cast<int>(players.size()))
    {
        // Get the selected player using playerNumber
        m_gameObject = players[playerNumber];
    }
}

void DamageCommand::Execute()
{
    // Reduce health by damage amount
    m_gameObject->GetComponent<game::Player>()->Die();
}


ScorePointCommand::ScorePointCommand(int playerNumber)
{
    const std::vector<dae::GameObject*> players = dae::SceneData::GetInstance().GetPlayers();

    if (playerNumber >= 0 && playerNumber < static_cast<int>(players.size()))
    {
        // Get the selected player using playerNumber
        m_gameObject = players[playerNumber];
    }
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

    message.arguments.emplace_back(static_cast<sound_id>(4)); // sound ID

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



void NavigateUpCommand::Execute() {
	if (const auto menu = FindMenuComponent()) {
        dae::Message message;

        message.type = dae::PlaySoundMessageType::deathSound;

        message.arguments.emplace_back(static_cast<sound_id>(20)); // sound ID

        dae::EventQueue::Broadcast(message);
        menu->NavigateUp();
    }
}

dae::MenuComponent* NavigateUpCommand::FindMenuComponent() {
	const auto& sceneManager = dae::SceneManager::GetInstance();
    const auto& currentScene = sceneManager.GetActiveScene();
    const auto& objects = currentScene->GetObjects();
    for (const auto& obj : objects) {
	    if (const auto menuComponent = obj->GetComponent<dae::MenuComponent>()) {
            return menuComponent;
        }
    }
    return nullptr;
}

void NavigateDownCommand::Execute() {
	if (const auto menu = FindMenuComponent()) {
        dae::Message message;

        message.type = dae::PlaySoundMessageType::deathSound;

        message.arguments.emplace_back(static_cast<sound_id>(20)); // sound ID

        dae::EventQueue::Broadcast(message);
        menu->NavigateDown();
    }
}

dae::MenuComponent* NavigateDownCommand::FindMenuComponent() {
	const auto& sceneManager = dae::SceneManager::GetInstance();
    const auto& currentScene = sceneManager.GetActiveScene();
    const auto& objects = currentScene->GetObjects();
    for (const auto& obj : objects) {
	    if (const auto menuComponent = obj->GetComponent<dae::MenuComponent>()) {
            return menuComponent;
        }
    }
    return nullptr;
}

void SelectOptionCommand::Execute() {
	if (const auto menu = FindMenuComponent()) {
        dae::Message message;

        message.type = dae::PlaySoundMessageType::deathSound;

        message.arguments.emplace_back(static_cast<sound_id>(18)); // sound ID

        dae::EventQueue::Broadcast(message);
        menu->SelectOption();
    }
}

dae::MenuComponent* SelectOptionCommand::FindMenuComponent() {
	const auto& sceneManager = dae::SceneManager::GetInstance();
    const auto& currentScene = sceneManager.GetActiveScene();
    const auto& objects = currentScene->GetObjects();
    for (const auto& obj : objects) {
	    if (const auto menuComponent = obj->GetComponent<dae::MenuComponent>()) {
            return menuComponent;
        }
    }
    return nullptr;
}



void NavigateUpLetterCommand::Execute() {
    if (const auto SelectName = FindSelectNameComponent()) {
        dae::Message message;

        message.type = dae::PlaySoundMessageType::deathSound;

        message.arguments.emplace_back(static_cast<sound_id>(20)); // sound ID

        dae::EventQueue::Broadcast(message);
        SelectName->AddLetter();
    }
}

SelectNameComponent* NavigateUpLetterCommand::FindSelectNameComponent() {
    const auto& sceneManager = dae::SceneManager::GetInstance();
    const auto& currentScene = sceneManager.GetActiveScene();
    const auto& objects = currentScene->GetObjects();
    for (const auto& obj : objects) {
        if (const auto selectNameComponent = obj->GetComponent<SelectNameComponent>()) {
            return selectNameComponent;
        }
    }
    return nullptr;
}

void NavigateDownLetterCommand::Execute() {
    if (const auto SelectName = FindSelectNameComponent()) {
        dae::Message message;

        message.type = dae::PlaySoundMessageType::deathSound;

        message.arguments.emplace_back(static_cast<sound_id>(20)); // sound ID

        dae::EventQueue::Broadcast(message);
        SelectName->SubtractLetter();
    }
}

SelectNameComponent* NavigateDownLetterCommand::FindSelectNameComponent() {
    const auto& sceneManager = dae::SceneManager::GetInstance();
    const auto& currentScene = sceneManager.GetActiveScene();
    const auto& objects = currentScene->GetObjects();
    for (const auto& obj : objects) {
        if (const auto selectNameComponent = obj->GetComponent<SelectNameComponent>()) {
            return selectNameComponent;
        }
    }
    return nullptr;
}

void SelectOptionLetterCommand::Execute() {
    if (const auto SelectName = FindSelectNameComponent()) {
        dae::Message message;

        message.type = dae::PlaySoundMessageType::deathSound;

        message.arguments.emplace_back(static_cast<sound_id>(18)); // sound ID

        dae::EventQueue::Broadcast(message);
        SelectName->ConfirmLetter();
    }
}

SelectNameComponent* SelectOptionLetterCommand::FindSelectNameComponent() {
    const auto& sceneManager = dae::SceneManager::GetInstance();
    const auto& currentScene = sceneManager.GetActiveScene();
    const auto& objects = currentScene->GetObjects();
    for (const auto& obj : objects) {
        if (const auto selectNameComponent = obj->GetComponent<SelectNameComponent>()) {
            return selectNameComponent;
        }
    }
    return nullptr;
}


void saveScoreCommand::Execute() {
    if (const auto SelectName = FindSelectNameComponent()) {
        m_currentname = SelectName->GetCurrentName();

        HighScores::GetInstance().saveNewScore(m_currentname, 2000);
		dae::SceneManager::GetInstance().SetActiveScene("ScoreboardScene");
    }
}

SelectNameComponent* saveScoreCommand::FindSelectNameComponent() {
    const auto& sceneManager = dae::SceneManager::GetInstance();
    const auto& currentScene = sceneManager.GetActiveScene();
    const auto& objects = currentScene->GetObjects();
    for (const auto& obj : objects) {
        if (const auto selectNameComponent = obj->GetComponent<SelectNameComponent>()) {
            return selectNameComponent;
        }
    }
    return nullptr;
}