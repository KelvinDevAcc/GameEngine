#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "AnimationComponent.h"
#include "FPSCounterComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Command.h"
#include "InputManager.h"
#include "HealthComponent.h"
#include "LivesDisplayComponent.h"
#include "Player.h"
#include "PointsDisplayComponent.h"
#include "RotatorComponent.h"
#include "sdl_sound_system.h"
#include "servicelocator.h"
#include "SpriteRenderer.h"

void LoadResources()
{
#if _DEBUG
    servicelocator::register_sound_system(
        std::make_unique<logging_sound_system>(std::make_unique<sdl_sound_system>()));
#else
    servicelocator::register_sound_system(std::make_unique<sdl_sound_system>());
#endif

    auto& ss = servicelocator::get_sound_system();

    // Register the sound file with its corresponding ID
    ss.register_sound_file("../Data/2.mp3");
    ss.register_sound_file("../Data/04 Lose Life.mp3");

    // Get the ID for the sound file path
    const sound_id soundId = ss.get_sound_id_for_file_path("../Data/04 Lose Life.mp3");

    ss.load_sound(soundId, "../Data/04 Lose Life.mp3");


	dae::ResourceManager::LoadFont("Lingua", "Lingua.otf", 36);
	dae::ResourceManager::LoadFont("Linguasmall", "Lingua.otf", 26);
	dae::ResourceManager::LoadFont("arcade", "arcade-legacy.ttf", 20);

	dae::ResourceManager::LoadSprite("background", "background.tga");
	dae::ResourceManager::LoadSprite("logo", "logo.tga");

	dae::ResourceManager::LoadSprite("Stage01", "Stage01.png");

    dae::ResourceManager::LoadSprite("sausage", "sausage.png");

    dae::ResourceManager::LoadSprite("chef",
        "Arcade - Burger Time - Characters & Objects-white.png",
        11,  // rowCount
        15,  // colCount
        {
            { "Idle", { { { 1, 0 }}, 1 } },
            { "Walk_Right", { { { 3, 0 }, { 4, 0 }, { 5, 0 } }, 4 } },
            { "Walk_Left", { { { 3, 0 }, { 4, 0 }, { 5, 0 } }, 4 } },
            { "Walk_Up", { { { 6, 0 }, { 7, 0 }, { 8, 0 } }, 4 } },
            { "Walk_Down", { { { 0, 0 }, { 1, 0 }, { 2, 0 } }, 4 } },
            { "Dying", { { { 3, 1 }, { 4, 1 }, { 5, 1 }, { 6, 1 }, { 7, 1 }, { 8, 1 } }, 2 } },
            { "Attacking", { { { 1, 1 } }, 1 } }
        });
    dae::ResourceManager::LoadSprite("egg",
        "Arcade - Burger Time - Characters & Objects-white.png",
        11,  // rowCount
        15,  // colCount
        {
            { "eggIdle", { { { 1, 6 }}, 1 } },
            { "eggWalk_Right", { { { 2, 6 }, { 3, 6 } }, 1 } },
            { "eggWalk_Left", { { { 2, 6 }, { 3, 6 } }, 1 } },
            { "eggWalk_Up", { { { 4, 6 }, { 4, 6 } }, 1 } },
            { "eggWalk_Down", { { { 0, 6 }, { 1, 6 } }, 1 } },
            { "eggDying", { { { 0, 7 }, { 1, 7 }, { 2, 7 }, { 3, 7 } }, 2 } },
            { "eggStunned", { { { 4, 7 }, { 5, 7 } }, 1 } }
        });

}


void HandlePlayerInput(const dae::InputManager& inputManager, dae::GameObject* player)
{


    inputManager.BindCommand(SDL_SCANCODE_W, KeyState::Pressed, std::make_unique<MoveCommand>(player, 0.0f, -3.0f), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_S, KeyState::Pressed, std::make_unique<MoveCommand>(player, 0.0f, 3.0f), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_A, KeyState::Pressed, std::make_unique<MoveCommand>(player, -3.0f, 0.0f), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_D, KeyState::Pressed, std::make_unique<MoveCommand>(player, 3.0f, 0.0f), InputType::Keyboard);

    inputManager.BindCommand(SDL_SCANCODE_X, KeyState::Up, std::make_unique<ScorePointCommand>(player), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_Z, KeyState::Up, std::make_unique<ScorePointCommand>(player), InputType::Keyboard);

    inputManager.BindCommand(SDL_SCANCODE_C, KeyState::Up, std::make_unique<DamageCommand>(player), InputType::Keyboard);

    inputManager.BindCommand(SDL_SCANCODE_M, KeyState::Up, std::make_unique<GoToNextSceneCommand>(), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_P, KeyState::Up, std::make_unique<PlaySoundCommand>(), InputType::Keyboard);
}


void Scene1(const dae::InputManager& inputManager, dae::Scene* scene)
{
    // Create GameObject for background
    auto backgroundObject = std::make_unique<dae::GameObject>();
    auto backgroundObjectreder = std::make_unique<dae::SpriteRenderer>(backgroundObject.get(), dae::ResourceManager::GetSprite("background"), glm::ivec2(0, 0));
    backgroundObjectreder->SetDimensions(1270,720);
    backgroundObject->SetLocalPosition(glm::vec3(635, 380, 0.f));
    backgroundObject->AddComponent(std::move(backgroundObjectreder));
    scene->Add(std::move(backgroundObject));

	// // Create GameObject for logo
    auto logoObject = std::make_unique<dae::GameObject>();
    auto logoRenderComponent = std::make_unique<dae::SpriteRenderer>(logoObject.get(), dae::ResourceManager::GetSprite("logo"), glm::ivec2(0, 0));
	logoObject->SetLocalPosition(glm::vec3(635.f, 360.f, 0.0f));
    logoObject->SetDimensions(10, 10);
    logoObject->AddComponent(std::move(logoRenderComponent));
    auto logoRotatorComponent = std::make_unique<dae::RotatorComponent>(logoObject.get(), 10.0f, 635.f, 360.f, 5.0f);
    logoObject->AddComponent(std::move(logoRotatorComponent));
    scene->Add(std::move(logoObject));

    // Create GameObject for Character 2
    auto CharacterObject2 = std::make_unique<dae::GameObject>();
    auto CharacterRenderComponent2 = std::make_unique<dae::SpriteRenderer>(CharacterObject2.get(),dae::ResourceManager::GetSprite("sausage"), glm::ivec2(0, 0));
    CharacterObject2->SetLocalPosition(glm::vec3(300.0f, 300.0f, 0.0f));
    CharacterRenderComponent2->SetDimensions(50, 50);

    auto Character2Health = std::make_unique<dae::HealthComponent>(100, 3); // Create HealthComponent with initial health 100 and lives 3
    auto Character2points = std::make_unique<dae::PointComponent>(0);

    // Bind commands for Character 2 movement using controller DPAD (controller)
	inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadUp), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), 0.0f, -10.0f), InputType::Controller);
    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadDown), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), 0.0f, 10.0f), InputType::Controller);
    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadLeft), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), -10.0f, 0.0f), InputType::Controller);
    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadRight), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), 10.0f, 0.0f), InputType::Controller);

    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::A), KeyState::Up, std::make_unique<ScorePointCommand>(CharacterObject2.get()), InputType::Controller);
    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::B), KeyState::Up, std::make_unique<ScorePointCommand>(CharacterObject2.get()), InputType::Controller);

    inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::X), KeyState::Down, std::make_unique<DamageCommand>(CharacterObject2.get()), InputType::Controller);

    // Add HealthComponent and PointComponent to CharacterObject2
    CharacterObject2->AddComponent(std::move(Character2Health));
    CharacterObject2->AddComponent(std::move(Character2points));
    CharacterObject2->AddComponent(std::move(CharacterRenderComponent2));

    // Create GameObject for displaying lives of Character 2
    auto livesDisplayObject2 = std::make_unique<dae::GameObject>();
    auto livesDisplayComponent2 = std::make_unique<dae::LivesDisplayComponent>(dae::ResourceManager::GetFont("arcade"), *livesDisplayObject2);
    auto character2HealthComponent = CharacterObject2->GetComponent<dae::HealthComponent>();
    livesDisplayComponent2->AttachToHealthComponent(character2HealthComponent);
    livesDisplayObject2->AddComponent(std::move(livesDisplayComponent2));
    livesDisplayObject2->SetLocalPosition(glm::vec3(100, 250, 0.f));

    // Create GameObject for displaying points of Character 2
    auto pointsDisplayObject2 = std::make_unique<dae::GameObject>();
    auto pointsDisplayComponent2 = std::make_unique<dae::PointsDisplayComponent>(dae::ResourceManager::GetFont("arcade"), *pointsDisplayObject2); // Assuming a font for displaying points
    auto character2PointComponent = CharacterObject2->GetComponent<dae::PointComponent>();
    pointsDisplayComponent2->AttachToPointComponent(character2PointComponent);
    pointsDisplayObject2->AddComponent(std::move(pointsDisplayComponent2));
    pointsDisplayObject2->SetLocalPosition(glm::vec3(100, 270, 0.f));

    scene->Add(std::move(pointsDisplayObject2));
    scene->Add(std::move(livesDisplayObject2));
    scene->Add(std::move(CharacterObject2));


    // Create GameObject for Character 
    auto characterObject = std::make_unique<dae::GameObject>();

    // Create and set up SpriteRenderer component
    auto spriteRendererComponent = std::make_unique<dae::SpriteRenderer>(characterObject.get(), dae::ResourceManager::GetSprite("chef"), glm::ivec2{ 0,0 });
    spriteRendererComponent->SetDimensions(60, 60);
    characterObject->AddComponent(std::move(spriteRendererComponent));

    // Create and set up AnimationComponent component
    auto animationComponent = std::make_unique<dae::AnimationComponent>(characterObject.get(), characterObject->GetComponent<dae::SpriteRenderer>(), "Idle");
    characterObject->AddComponent(std::move(animationComponent));

    auto healthComponent = std::make_unique<dae::HealthComponent>(100, 3);
    auto pointComponent = std::make_unique<dae::PointComponent>(0);

    characterObject->AddComponent(std::move(healthComponent));
    characterObject->AddComponent(std::move(pointComponent));

    characterObject->SetLocalPosition(glm::vec3(221.0f, 281.0f, 0.0f));

    auto playerComponent = std::make_unique<game::Player>(characterObject.get());
    characterObject->AddComponent(std::move(playerComponent));

    HandlePlayerInput(inputManager, characterObject.get());

    auto livesDisplayObject = std::make_unique<dae::GameObject>();
    auto livesDisplayComponent = std::make_unique<dae::LivesDisplayComponent>(dae::ResourceManager::GetFont("arcade"), *livesDisplayObject);
    auto character1HealthComponent = characterObject->GetComponent<dae::HealthComponent>();
    livesDisplayComponent->AttachToHealthComponent(character1HealthComponent);
    livesDisplayObject->AddComponent(std::move(livesDisplayComponent));
    livesDisplayObject->SetLocalPosition(glm::vec3(100, 450, 0.f));

    auto pointsDisplayObject = std::make_unique<dae::GameObject>();
    auto pointsDisplayComponent = std::make_unique<dae::PointsDisplayComponent>(dae::ResourceManager::GetFont("arcade"), *pointsDisplayObject); // Assuming a font for displaying points
    auto characterPointComponent = characterObject->GetComponent<dae::PointComponent>();
    pointsDisplayComponent->AttachToPointComponent(characterPointComponent);
    pointsDisplayObject->AddComponent(std::move(pointsDisplayComponent));
    pointsDisplayObject->SetLocalPosition(glm::vec3(100, 470, 0.f));

    scene->Add(std::move(pointsDisplayObject));
    scene->Add(std::move(livesDisplayObject));
    scene->Add(std::move(characterObject));

    // Create GameObject for Title
    auto TitleObject = std::make_unique<dae::GameObject>();
    auto titleTextComponent = std::make_unique<dae::TextComponent>("Programming 4 Assignment", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 255, 255, 255, 255 }, *TitleObject); // Pass the GameObject reference here
    TitleObject->SetLocalPosition(glm::vec3(635, 20, 0.f));
    TitleObject->AddComponent(std::move(titleTextComponent));
    scene->Add(std::move(TitleObject));

    // Create GameObject for Title
    auto NextSceneTextobject = std::make_unique<dae::GameObject>();
    auto NextSceneComponent = std::make_unique<dae::TextComponent>("M to go to next scene", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 255, 255, 255, 255 }, *NextSceneTextobject); // Pass the GameObject reference here
    NextSceneTextobject->SetLocalPosition(glm::vec3(635, 60, 0.f));
    NextSceneTextobject->AddComponent(std::move(NextSceneComponent));
    scene->Add(std::move(NextSceneTextobject));

    // Create GameObject for text shef
    auto Infocharacter1Txt = std::make_unique<dae::GameObject>();
    auto character1textcomponent = std::make_unique<dae::TextComponent>("Use WASD to move chef", dae::ResourceManager::GetFont("Linguasmall"), SDL_Color{ 255, 255, 255, 255 }, *Infocharacter1Txt); // Specify color here
    Infocharacter1Txt->AddComponent(std::move(character1textcomponent));
    Infocharacter1Txt->SetLocalPosition(glm::vec3(130, 150, 0.f));
    scene->Add(std::move(Infocharacter1Txt));

    // Create GameObject for text sausage
    auto Infocharacter2Txt = std::make_unique<dae::GameObject>();
    auto character2textcomponent = std::make_unique<dae::TextComponent>("Use D-Pad to move sausage", dae::ResourceManager::GetFont("Linguasmall"), SDL_Color{ 255, 255, 255, 255 }, *Infocharacter2Txt); // Specify color here
    Infocharacter2Txt->AddComponent(std::move(character2textcomponent));
    Infocharacter2Txt->SetLocalPosition(glm::vec3(145, 170, 0.f));
    scene->Add(std::move(Infocharacter2Txt));

    // Create GameObject for text shef
    auto InfoSoundTxt = std::make_unique<dae::GameObject>();
    auto soundTextcomponent = std::make_unique<dae::TextComponent>("use P to play sound", dae::ResourceManager::GetFont("Linguasmall"), SDL_Color{ 255, 255, 255, 255 }, *InfoSoundTxt); // Specify color here
    InfoSoundTxt->AddComponent(std::move(soundTextcomponent));
    InfoSoundTxt->SetLocalPosition(glm::vec3(130, 100, 0.f));
    scene->Add(std::move(InfoSoundTxt));


    //Create GameObject for FPS counter
    auto fpsCounterObject = std::make_unique<dae::GameObject>();
    auto fpsTextComponent = std::make_unique<dae::TextComponent>("FPS: ", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 252, 157, 3, 255 }, *fpsCounterObject); // Specify color here
    auto fpsCounterComponent = std::make_unique<dae::FPSCounterComponent>(fpsTextComponent.get());

    fpsCounterObject->AddComponent(std::move(fpsCounterComponent));
    fpsCounterObject->AddComponent(std::move(fpsTextComponent));
    fpsCounterObject->SetLocalPosition(glm::vec3(100.f, 20.f, 0.0f));
    scene->Add(std::move(fpsCounterObject));
}

void Scene2(dae::Scene* scene)
{

    // Create GameObject for FPS counter
    auto fpsCounterObject1 = std::make_unique<dae::GameObject>();
    auto fpsTextComponent1 = std::make_unique<dae::TextComponent>("FPS: ", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 252, 157, 3, 255 }, *fpsCounterObject1); // Specify color here
    auto fpsCounterComponent1 = std::make_unique<dae::FPSCounterComponent>(fpsTextComponent1.get());
    fpsCounterObject1->SetLocalPosition(glm::vec3(100.f, 20.f, 0.0f));
    fpsCounterObject1->AddComponent(std::move(fpsTextComponent1));
    fpsCounterObject1->AddComponent(std::move(fpsCounterComponent1));
    scene->Add(std::move(fpsCounterObject1));


    // Create GameObject for Title
    auto TitleObject02 = std::make_unique<dae::GameObject>();
    auto titleTextComponent02 = std::make_unique<dae::TextComponent>("BURGERTIME", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 255, 0, 0, 255 }, *TitleObject02); // Pass the GameObject reference here
    TitleObject02->SetLocalPosition(glm::vec3(635, 70, 0.f));
    TitleObject02->AddComponent(std::move(titleTextComponent02));
    scene->Add(std::move(TitleObject02));

    // Create GameObject for text shef
    auto Infocharacter1Txt02 = std::make_unique<dae::GameObject>();
    auto character1textcomponent02 = std::make_unique<dae::TextComponent>("@ CORP 1982 DATA EAST INC", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 255, 0, 0, 255 }, *Infocharacter1Txt02); // Specify color here
    Infocharacter1Txt02->AddComponent(std::move(character1textcomponent02));
    Infocharacter1Txt02->SetLocalPosition(glm::vec3(635, 140, 0.f));
    scene->Add(std::move(Infocharacter1Txt02));

    // Create GameObject for text sausage
    auto Infocharacter2Txt02 = std::make_unique<dae::GameObject>();
    auto character2textcomponent02 = std::make_unique<dae::TextComponent>("MFGD BY BALLY MIDWAY MFG, CO,", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 255, 0, 0, 255 }, *Infocharacter2Txt02); // Specify color here
    Infocharacter2Txt02->AddComponent(std::move(character2textcomponent02));
    Infocharacter2Txt02->SetLocalPosition(glm::vec3(635, 170, 0.f));
    scene->Add(std::move(Infocharacter2Txt02));
}

void Scene3(const dae::InputManager& /*inputManager*/, dae::Scene* scene)
{
    // Create GameObject for background
    auto backgroundObject03 = std::make_unique<dae::GameObject>();
    auto backgroundRenderComponent03 = std::make_unique<dae::SpriteRenderer>(backgroundObject03.get(),dae::ResourceManager::GetSprite("Stage01"));
    backgroundRenderComponent03->SetDimensions(624, 600);
    backgroundObject03->SetLocalPosition(glm::vec3(635, 360, 0.f));
    backgroundObject03->AddComponent(std::move(backgroundRenderComponent03));
    scene->Add(std::move(backgroundObject03));

    // Create GameObject for FPS counter 2
    auto fpsCounterObject2 = std::make_unique<dae::GameObject>();
    auto fpsTextComponent2 = std::make_unique<dae::TextComponent>("FPS: ", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 252, 157, 3, 255 }, *fpsCounterObject2); // Specify color here
    auto fpsCounterComponent2 = std::make_unique<dae::FPSCounterComponent>(fpsTextComponent2.get());
    fpsCounterObject2->AddComponent(std::move(fpsTextComponent2));
    fpsCounterObject2->AddComponent(std::move(fpsCounterComponent2));

    fpsCounterObject2->SetLocalPosition(glm::vec3(100.f, 20.f, 0.0f));
    scene->Add(std::move(fpsCounterObject2));


    // Create GameObject for Character 1
    auto CharacterObject1 = std::make_unique<dae::GameObject>();

    // Create and set up SpriteRenderer component
    auto spriterenderComponent = std::make_unique<dae::SpriteRenderer>(CharacterObject1.get(), dae::ResourceManager::GetSprite("chef"), glm::ivec2{ 0,0 });
    spriterenderComponent->SetDimensions(40, 40);
    CharacterObject1->AddComponent(std::move(spriterenderComponent));

    // Create and set up AnimationComponent component
    auto animationComponent = std::make_unique<dae::AnimationComponent>(CharacterObject1.get(), CharacterObject1->GetComponent<dae::SpriteRenderer>(), "Idle");
    CharacterObject1->AddComponent(std::move(animationComponent));

    auto Character1Health = std::make_unique<dae::HealthComponent>(100, 3);
	auto Character1points = std::make_unique<dae::PointComponent>(0);


    CharacterObject1->AddComponent(std::move(Character1Health));
    CharacterObject1->AddComponent(std::move(Character1points));

    CharacterObject1->SetLocalPosition(glm::vec3(121.0f, 81.0f, 0.0f));

    auto PlayerComponent = std::make_unique<game::Player>(CharacterObject1.get());
    CharacterObject1->AddComponent(std::move(PlayerComponent));


    //HandlePlayerInput(inputManager, CharacterObject1.get());


	auto livesDisplayObject2 = std::make_unique<dae::GameObject>();
    auto livesDisplayComponent2 = std::make_unique<dae::LivesDisplayComponent>(dae::ResourceManager::GetFont("arcade"), *livesDisplayObject2);
    auto character2HealthComponent = CharacterObject1->GetComponent<dae::HealthComponent>();
    livesDisplayComponent2->AttachToHealthComponent(character2HealthComponent);
    livesDisplayObject2->AddComponent(std::move(livesDisplayComponent2));
    livesDisplayObject2->SetLocalPosition(glm::vec3(100, 250, 0.f));

    auto pointsDisplayObject2 = std::make_unique<dae::GameObject>();
    auto pointsDisplayComponent2 = std::make_unique<dae::PointsDisplayComponent>(dae::ResourceManager::GetFont("arcade"), *pointsDisplayObject2); // Assuming a font for displaying points
    auto character2PointComponent = CharacterObject1->GetComponent<dae::PointComponent>();
    pointsDisplayComponent2->AttachToPointComponent(character2PointComponent);
    pointsDisplayObject2->AddComponent(std::move(pointsDisplayComponent2));
    pointsDisplayObject2->SetLocalPosition(glm::vec3(100, 270, 0.f));

    scene->Add(std::move(pointsDisplayObject2));
    scene->Add(std::move(livesDisplayObject2));
    scene->Add(std::move(CharacterObject1));



    auto eggObject = std::make_unique<dae::GameObject>();

    auto eggspriterenderComponent = std::make_unique<dae::SpriteRenderer>(eggObject.get(), dae::ResourceManager::GetSprite("egg"), glm::ivec2{ 0,0 });
    eggspriterenderComponent->SetDimensions(40, 40);
    eggObject->AddComponent(std::move(eggspriterenderComponent));

    auto egganimationComponent = std::make_unique<dae::AnimationComponent>(eggObject.get(), eggObject->GetComponent<dae::SpriteRenderer>(), "eggIdle");
    egganimationComponent->Play("eggStunned", true);
	eggObject->AddComponent(std::move(egganimationComponent));

    eggObject->SetLocalPosition(glm::vec3(221.0f, 81.0f, 0.0f));
    scene->Add(std::move(eggObject));

}


void load()
{
    LoadResources();

    auto& sceneManager = dae::SceneManager::GetInstance();
    const auto& inputManager = dae::InputManager::GetInstance();

    const auto& scene = sceneManager.CreateScene("Scene1");
    const auto& scene2 = sceneManager.CreateScene("Scene2");
    const auto& scene3 = sceneManager.CreateScene("Scene3");


    Scene1(inputManager, scene);
    Scene2(scene2);
    Scene3(inputManager, scene3);


    sceneManager.SetActiveScene("Scene1");

}

int main(int, char* []) {
    dae::Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}