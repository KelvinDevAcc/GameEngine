#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include <iostream>
#include <ostream>
#include <steam_api.h>

#include "FPSCounterComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Command.h"
#include "InputManager.h"
#include "RotatorComponent.h"
#include "GameController.h"
#include "HealthComponent.h"
#include "LivesDisplayComponent.h"
#include "PointsDisplayComponent.h"


void load()
{
    const auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    ///dae::InputManager inputManager;

    const auto& inputManager = dae::InputManager::GetInstance();

    // Create GameObject for background
    auto backgroundObject = std::make_unique<dae::GameObject>();
    auto backgroundRenderComponent = std::make_unique<dae::RenderComponent>();
    backgroundRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.tga"));
    backgroundRenderComponent->SetDimensions(1270, 720);
    backgroundObject->SetLocalPosition(glm::vec3(635, 720, 0.f));
    backgroundObject->AddComponent(std::move(backgroundRenderComponent));
    scene->Add(std::move(backgroundObject));

    // Create GameObject for logo
    auto logoObject = std::make_unique<dae::GameObject>();
    auto logoRenderComponent = std::make_unique<dae::RenderComponent>();
    logoRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.tga"));
    logoObject->SetLocalPosition(glm::vec3(635.f, 360.f, 0.0f));
    logoObject->AddComponent(std::move(logoRenderComponent));
    auto logoRotatorComponent = std::make_unique<dae::RotatorComponent>(10.0f, 635.f, 360.f, 5.0f);
    logoObject->AddComponent(std::move(logoRotatorComponent));
    scene->Add(std::move(logoObject));

    // Create GameObject for Character 1
    auto CharacterObject1 = std::make_unique<dae::GameObject>();
    auto CharacterRenderComponent1 = std::make_unique<dae::RenderComponent>();
    CharacterRenderComponent1->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Character.png"));
    CharacterRenderComponent1->SetDimensions(50, 50);
    CharacterObject1->SetLocalPosition(glm::vec3(250.0f, 300.0f, 0.0f));

    // Create HealthComponent and PointComponent
    auto Character1Health = std::make_unique<dae::HealthComponent>(100, 3);
    auto Character1points = std::make_unique<dae::PointComponent>(0);

    // Bind commands for Character 1 movement using WASD (keyboard)
    inputManager.BindCommand(SDL_SCANCODE_W, KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject1.get(), 0.0f, -5.0f), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_S, KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject1.get(), 0.0f, 5.0f), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_A, KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject1.get(), -5.0f, 0.0f), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_D, KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject1.get(), 5.0f, 0.0f), InputType::Keyboard);

    inputManager.BindCommand(SDL_SCANCODE_X, KeyState::Up, std::make_unique<ScorePointCommand>(Character1points.get(), 100), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_Z, KeyState::Up, std::make_unique<ScorePointCommand>(Character1points.get(), 100), InputType::Keyboard);

	inputManager.BindCommand(SDL_SCANCODE_C, KeyState::Up, std::make_unique<DamageCommand>(Character1Health.get(), 100), InputType::Keyboard);


    // Add HealthComponent and PointComponent to CharacterObject1
    CharacterObject1->AddComponent(std::move(Character1Health));
    CharacterObject1->AddComponent(std::move(Character1points));
    CharacterObject1->AddComponent(std::move(CharacterRenderComponent1));

    // Create GameObject for displaying lives
    auto livesDisplayObject1 = std::make_unique<dae::GameObject>();
    auto livesDisplayComponent1 = std::make_unique<dae::LivesDisplayComponent>(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
    auto character1HealthComponent = CharacterObject1->GetComponent<dae::HealthComponent>();
    livesDisplayComponent1->AttachToHealthComponent(character1HealthComponent);
    livesDisplayObject1->AddComponent(std::move(livesDisplayComponent1));
    livesDisplayObject1->SetLocalPosition(glm::vec3(70, 200, 0.f));

	//Create GameObject for displaying points of Character 1
    auto pointsDisplayObject1 = std::make_unique<dae::GameObject>();
    auto pointsDisplayComponent1 = std::make_unique<dae::PointsDisplayComponent>(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)); // Assuming a font for displaying points
    auto character1PointComponent = CharacterObject1->GetComponent<dae::PointComponent>();
    pointsDisplayComponent1->AttachToPointComponent(character1PointComponent);
    pointsDisplayObject1->AddComponent(std::move(pointsDisplayComponent1));
    pointsDisplayObject1->SetLocalPosition(glm::vec3(70, 220, 0.f));

	scene->Add(std::move(pointsDisplayObject1));
    scene->Add(std::move(livesDisplayObject1));
    scene->Add(std::move(CharacterObject1));

    

    // Create GameObject for Character 2
    auto CharacterObject2 = std::make_unique<dae::GameObject>();
    auto CharacterRenderComponent2 = std::make_unique<dae::RenderComponent>();
    CharacterRenderComponent2->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("sausage.png"));
    CharacterRenderComponent2->SetDimensions(50, 50);
    CharacterObject2->SetLocalPosition(glm::vec3(200.0f, 300.0f, 0.0f));

    auto Character2Health = std::make_unique<dae::HealthComponent>(100, 3); // Create HealthComponent with initial health 100 and lives 3
    auto Character2points = std::make_unique<dae::PointComponent>(0);

    // Bind commands for Character 2 movement using controller DPAD (controller)
    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadUp), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), 0.0f, -10.0f), InputType::Controller);
    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadDown), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), 0.0f, 10.0f), InputType::Controller);
    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadLeft), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), -10.0f, 0.0f), InputType::Controller);
    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadRight), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), 10.0f, 0.0f), InputType::Controller);

    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::A), KeyState::Up, std::make_unique<ScorePointCommand>(Character2points.get(), 100), InputType::Controller);
    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::B), KeyState::Up, std::make_unique<ScorePointCommand>(Character2points.get(), 100), InputType::Controller);

	inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::X), KeyState::Down, std::make_unique<DamageCommand>(Character2Health.get(), 100), InputType::Controller);

    // Add HealthComponent and PointComponent to CharacterObject2
    CharacterObject2->AddComponent(std::move(Character2Health));
    CharacterObject2->AddComponent(std::move(Character2points));
    CharacterObject2->AddComponent(std::move(CharacterRenderComponent2));

    // Create GameObject for displaying lives of Character 2
    auto livesDisplayObject2 = std::make_unique<dae::GameObject>();
    auto livesDisplayComponent2 = std::make_unique<dae::LivesDisplayComponent>(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
    auto character2HealthComponent = CharacterObject2->GetComponent<dae::HealthComponent>();
    livesDisplayComponent2->AttachToHealthComponent(character2HealthComponent);
    livesDisplayObject2->AddComponent(std::move(livesDisplayComponent2));
    livesDisplayObject2->SetLocalPosition(glm::vec3(70, 250, 0.f));

    // Create GameObject for displaying points of Character 2
    auto pointsDisplayObject2 = std::make_unique<dae::GameObject>();
    auto pointsDisplayComponent2 = std::make_unique<dae::PointsDisplayComponent>(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20)); // Assuming a font for displaying points
    auto character2PointComponent = CharacterObject2->GetComponent<dae::PointComponent>();
    pointsDisplayComponent2->AttachToPointComponent(character2PointComponent);
    pointsDisplayObject2->AddComponent(std::move(pointsDisplayComponent2));
    pointsDisplayObject2->SetLocalPosition(glm::vec3(70, 270, 0.f));

    scene->Add(std::move(pointsDisplayObject2));
    scene->Add(std::move(livesDisplayObject2));
    scene->Add(std::move(CharacterObject2));


    

    // Create GameObject for Title
    auto TitleObject = std::make_unique<dae::GameObject>();
    auto titleTextComponent = std::make_unique<dae::TextComponent>("Programming 4 Assignment", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
    TitleObject->AddComponent(std::move(titleTextComponent));
    TitleObject->SetLocalPosition(glm::vec3(635, 20, 0.f));
    scene->Add(std::move(TitleObject));

    // Create GameObject for text shef
    auto Infocharacter1Txt = std::make_unique<dae::GameObject>();
    auto character1textcomponent = std::make_unique<dae::TextComponent>("Use WASD to move chef, C to inflict damage, Z and X to pick up pellets", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
    Infocharacter1Txt->AddComponent(std::move(character1textcomponent));
    Infocharacter1Txt->SetLocalPosition(glm::vec3(330, 130, 0.f));
    scene->Add(std::move(Infocharacter1Txt));

    // Create GameObject for text sausage
    auto Infocharacter2Txt = std::make_unique<dae::GameObject>();
    auto character2textcomponent = std::make_unique<dae::TextComponent>("Use D-Pad to move sausage X to inflict damage, A and B to pick up pellets", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
    Infocharacter2Txt->AddComponent(std::move(character2textcomponent));
    Infocharacter2Txt->SetLocalPosition(glm::vec3(348, 150, 0.f));
    scene->Add(std::move(Infocharacter2Txt));


    // Create GameObject for FPS counter
    auto fpsCounterObject = std::make_unique<dae::GameObject>();
    auto fpsCounterComponent = std::make_unique<dae::FPSCounterComponent>();
    fpsCounterObject->AddComponent(std::move(fpsCounterComponent));

    //// Create TextComponent for displaying FPS
    auto fpsTextComponent = std::make_unique<dae::TextComponent>("FPS: ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
    fpsCounterObject->AddComponent(std::move(fpsTextComponent));
    fpsCounterObject->SetLocalPosition(glm::vec3(100.f, 20.f, 0.0f));
    scene->Add(std::move(fpsCounterObject));

    SteamAPI_RunCallbacks();

}

int main(int, char* []) {
    if (!SteamAPI_Init())
    {
        std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
        return 1;
    }
    else
        std::cout << "Successfully initialized steam." << std::endl;

    dae::Minigin engine("../Data/");
    engine.Run(load);
    SteamAPI_Shutdown();
    return 0;
}