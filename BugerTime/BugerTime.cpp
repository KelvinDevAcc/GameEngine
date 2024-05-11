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
#include "RenderComponent.h"
#include "Command.h"
#include "InputManager.h"
#include "HealthComponent.h"
#include "LivesDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "Renderer.h"
#include "RotatorComponent.h"
#include "sdl_sound_system.h"
#include "servicelocator.h"


void HandlePlayerInput(const dae::InputManager& inputManager, dae::GameObject* player , dae::AnimationComponent* animation_component)
{

    inputManager.BindCommand(SDL_SCANCODE_W, KeyState::Pressed, std::make_unique<MoveCommand>(player, 0.0f, -3.0f, animation_component), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_S, KeyState::Pressed, std::make_unique<MoveCommand>(player, 0.0f, 3.0f, animation_component), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_A, KeyState::Pressed, std::make_unique<MoveCommand>(player, -3.0f, 0.0f, animation_component), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_D, KeyState::Pressed, std::make_unique<MoveCommand>(player, 3.0f, 0.0f, animation_component), InputType::Keyboard);

    inputManager.BindCommand(SDL_SCANCODE_X, KeyState::Up, std::make_unique<ScorePointCommand>(player, 100), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_Z, KeyState::Up, std::make_unique<ScorePointCommand>(player, 100), InputType::Keyboard);

    inputManager.BindCommand(SDL_SCANCODE_C, KeyState::Up, std::make_unique<DamageCommand>(player, 100), InputType::Keyboard);

    inputManager.BindCommand(SDL_SCANCODE_M, KeyState::Up, std::make_unique<GoToNextSceneCommand>(), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_P, KeyState::Up, std::make_unique<PlaySoundCommand>(), InputType::Keyboard);
}


void Scene1(const dae::InputManager& /*inputManager*/, dae::Scene* scene)
{
    // Create GameObject for background
    auto backgroundObject = std::make_unique<dae::GameObject>();
    auto backgroundRenderComponent = std::make_unique<dae::RenderComponent>(backgroundObject.get());
    backgroundRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.tga"));
    backgroundRenderComponent->SetDimensions(1270, 720);
    backgroundObject->SetLocalPosition(glm::vec3(635, 720, 0.f));
    backgroundObject->AddComponent(std::move(backgroundRenderComponent));
    scene->Add(std::move(backgroundObject));

    // Create GameObject for logo
    auto logoObject = std::make_unique<dae::GameObject>();
    auto logoRenderComponent = std::make_unique<dae::RenderComponent>(logoObject.get());
    logoRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.tga"));
    logoObject->SetLocalPosition(glm::vec3(635.f, 360.f, 0.0f));
    logoObject->AddComponent(std::move(logoRenderComponent));
    auto logoRotatorComponent = std::make_unique<dae::RotatorComponent>(logoObject.get(), 10.0f, 635.f, 360.f, 5.0f);
    logoObject->AddComponent(std::move(logoRotatorComponent));
    scene->Add(std::move(logoObject));

    // Create GameObject for Character 2
 //   auto CharacterObject2 = std::make_unique<dae::GameObject>();
 //   auto CharacterRenderComponent2 = std::make_unique<dae::RenderComponent>(CharacterObject2.get());
 //   CharacterRenderComponent2->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("sausage.png"));
 //   CharacterRenderComponent2->SetDimensions(50, 50);
 //   CharacterObject2->SetLocalPosition(glm::vec3(200.0f, 300.0f, 0.0f));

 //   auto Character2Health = std::make_unique<dae::HealthComponent>(100, 3); // Create HealthComponent with initial health 100 and lives 3
 //   auto Character2points = std::make_unique<dae::PointComponent>(0);

 //   // Bind commands for Character 2 movement using controller DPAD (controller)
	////inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadUp), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), 0.0f, -10.0f, 0, 0), InputType::Controller);
 //   //inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadDown), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), 0.0f, 10.0f, 0,0), InputType::Controller);
 //   //inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadLeft), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), -10.0f, 0.0f), InputType::Controller);
 //   //inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::DPadRight), KeyState::Pressed, std::make_unique<MoveCommand>(CharacterObject2.get(), 10.0f, 0.0f), InputType::Controller);

 //   inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::A), KeyState::Up, std::make_unique<ScorePointCommand>(CharacterObject2.get(), 100), InputType::Controller);
 //   inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::B), KeyState::Up, std::make_unique<ScorePointCommand>(CharacterObject2.get(), 100), InputType::Controller);

 //   inputManager.BindCommand(GameController::GetButtonMapping(GameController::Button::X), KeyState::Down, std::make_unique<DamageCommand>(CharacterObject2.get(), 100), InputType::Controller);

 //   // Add HealthComponent and PointComponent to CharacterObject2
 //   CharacterObject2->AddComponent(std::move(Character2Health));
 //   CharacterObject2->AddComponent(std::move(Character2points));
 //   CharacterObject2->AddComponent(std::move(CharacterRenderComponent2));

 //   // Create GameObject for displaying lives of Character 2
 //   auto livesDisplayObject2 = std::make_unique<dae::GameObject>();
 //   auto livesDisplayComponent2 = std::make_unique<dae::LivesDisplayComponent>(dae::ResourceManager::GetInstance().LoadFont("arcade-legacy.ttf", 20), *livesDisplayObject2);
 //   auto character2HealthComponent = CharacterObject2->GetComponent<dae::HealthComponent>();
 //   livesDisplayComponent2->AttachToHealthComponent(character2HealthComponent);
 //   livesDisplayObject2->AddComponent(std::move(livesDisplayComponent2));
 //   livesDisplayObject2->SetLocalPosition(glm::vec3(100, 250, 0.f));

 //   // Create GameObject for displaying points of Character 2
 //   auto pointsDisplayObject2 = std::make_unique<dae::GameObject>();
 //   auto pointsDisplayComponent2 = std::make_unique<dae::PointsDisplayComponent>(dae::ResourceManager::GetInstance().LoadFont("arcade-legacy.ttf", 20), *pointsDisplayObject2); // Assuming a font for displaying points
 //   auto character2PointComponent = CharacterObject2->GetComponent<dae::PointComponent>();
 //   pointsDisplayComponent2->AttachToPointComponent(character2PointComponent);
 //   pointsDisplayObject2->AddComponent(std::move(pointsDisplayComponent2));
 //   pointsDisplayObject2->SetLocalPosition(glm::vec3(100, 270, 0.f));

 //   scene->Add(std::move(pointsDisplayObject2));
 //   scene->Add(std::move(livesDisplayObject2));
 //   scene->Add(std::move(CharacterObject2));

    // Create GameObject for Title
    auto TitleObject = std::make_unique<dae::GameObject>();
    auto titleTextComponent = std::make_unique<dae::TextComponent>("Programming 4 Assignment", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), SDL_Color{ 255, 255, 255, 255 }, *TitleObject); // Pass the GameObject reference here
    TitleObject->SetLocalPosition(glm::vec3(635, 20, 0.f));
    TitleObject->AddComponent(std::move(titleTextComponent));
    scene->Add(std::move(TitleObject));

    // Create GameObject for text shef
    auto Infocharacter1Txt = std::make_unique<dae::GameObject>();
    auto character1textcomponent = std::make_unique<dae::TextComponent>("Use WASD to move chef", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20), SDL_Color{ 255, 255, 255, 255 }, *Infocharacter1Txt); // Specify color here
    Infocharacter1Txt->AddComponent(std::move(character1textcomponent));
    Infocharacter1Txt->SetLocalPosition(glm::vec3(130, 150, 0.f));
    scene->Add(std::move(Infocharacter1Txt));

    // Create GameObject for text sausage
    auto Infocharacter2Txt = std::make_unique<dae::GameObject>();
    auto character2textcomponent = std::make_unique<dae::TextComponent>("Use D-Pad to move sausage", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20), SDL_Color{ 255, 255, 255, 255 }, *Infocharacter2Txt); // Specify color here
    Infocharacter2Txt->AddComponent(std::move(character2textcomponent));
    Infocharacter2Txt->SetLocalPosition(glm::vec3(145, 170, 0.f));
    scene->Add(std::move(Infocharacter2Txt));

    // Create GameObject for text shef
    auto InfoSoundTxt = std::make_unique<dae::GameObject>();
    auto soundTextcomponent = std::make_unique<dae::TextComponent>("use P to play sound", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20), SDL_Color{ 255, 255, 255, 255 }, *InfoSoundTxt); // Specify color here
    InfoSoundTxt->AddComponent(std::move(soundTextcomponent));
    InfoSoundTxt->SetLocalPosition(glm::vec3(130, 100, 0.f));
    scene->Add(std::move(InfoSoundTxt));


    //Create GameObject for FPS counter
    auto fpsCounterObject = std::make_unique<dae::GameObject>();
    auto fpsTextComponent = std::make_unique<dae::TextComponent>("FPS: ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), SDL_Color{ 252, 157, 3, 255 }, *fpsCounterObject); // Specify color here
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
    auto fpsTextComponent1 = std::make_unique<dae::TextComponent>("FPS: ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), SDL_Color{ 252, 157, 3, 255 }, *fpsCounterObject1); // Specify color here
    auto fpsCounterComponent1 = std::make_unique<dae::FPSCounterComponent>(fpsTextComponent1.get());
    fpsCounterObject1->SetLocalPosition(glm::vec3(100.f, 20.f, 0.0f));
    fpsCounterObject1->AddComponent(std::move(fpsTextComponent1));
    fpsCounterObject1->AddComponent(std::move(fpsCounterComponent1));
    scene->Add(std::move(fpsCounterObject1));


    // Create GameObject for Title
    auto TitleObject02 = std::make_unique<dae::GameObject>();
    auto titleTextComponent02 = std::make_unique<dae::TextComponent>("BURGERTIME", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 50), SDL_Color{ 255, 0, 0, 255 }, *TitleObject02); // Pass the GameObject reference here
    TitleObject02->SetLocalPosition(glm::vec3(635, 70, 0.f));
    TitleObject02->AddComponent(std::move(titleTextComponent02));
    scene->Add(std::move(TitleObject02));

    // Create GameObject for text shef
    auto Infocharacter1Txt02 = std::make_unique<dae::GameObject>();
    auto character1textcomponent02 = std::make_unique<dae::TextComponent>("@ CORP 1982 DATA EAST INC", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30), SDL_Color{ 255, 0, 0, 255 }, *Infocharacter1Txt02); // Specify color here
    Infocharacter1Txt02->AddComponent(std::move(character1textcomponent02));
    Infocharacter1Txt02->SetLocalPosition(glm::vec3(635, 140, 0.f));
    scene->Add(std::move(Infocharacter1Txt02));

    // Create GameObject for text sausage
    auto Infocharacter2Txt02 = std::make_unique<dae::GameObject>();
    auto character2textcomponent02 = std::make_unique<dae::TextComponent>("MFGD BY BALLY MIDWAY MFG, CO,", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30), SDL_Color{ 255, 0, 0, 255 }, *Infocharacter2Txt02); // Specify color here
    Infocharacter2Txt02->AddComponent(std::move(character2textcomponent02));
    Infocharacter2Txt02->SetLocalPosition(glm::vec3(635, 170, 0.f));
    scene->Add(std::move(Infocharacter2Txt02));
}

void Scene3(const dae::InputManager& inputManager, dae::Scene* scene)
{
    // Create GameObject for background
    auto backgroundObject03 = std::make_unique<dae::GameObject>();
    auto backgroundRenderComponent03 = std::make_unique<dae::RenderComponent>(backgroundObject03.get());
    backgroundRenderComponent03->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Stage01.png"));
    backgroundRenderComponent03->SetDimensions(624, 600);
    backgroundObject03->SetLocalPosition(glm::vec3(635, 360, 0.f));
    backgroundObject03->AddComponent(std::move(backgroundRenderComponent03));
    scene->Add(std::move(backgroundObject03));

    // Create GameObject for FPS counter 2
    auto fpsCounterObject2 = std::make_unique<dae::GameObject>();
    auto fpsTextComponent2 = std::make_unique<dae::TextComponent>("FPS: ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), SDL_Color{ 252, 157, 3, 255 }, *fpsCounterObject2); // Specify color here
    auto fpsCounterComponent2 = std::make_unique<dae::FPSCounterComponent>(fpsTextComponent2.get());
    fpsCounterObject2->AddComponent(std::move(fpsTextComponent2));
    fpsCounterObject2->AddComponent(std::move(fpsCounterComponent2));

    fpsCounterObject2->SetLocalPosition(glm::vec3(100.f, 20.f, 0.0f));
    scene->Add(std::move(fpsCounterObject2));


    //Create GameObject for Character 1
    auto CharacterObject13 = std::make_unique<dae::GameObject>();
   /* auto CharacterRenderComponent13 = std::make_unique<dae::RenderComponent>(CharacterObject13.get());
    CharacterRenderComponent13->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Character.png"));
    CharacterRenderComponent13->SetDimensions(30, 30);*/
    //auto spriteSheet = dae::ResourceManager::GetInstance().LoadSpriteSheet("CharacterWalkAnimation144x16-2.png", 16, 16, 3);

    dae::AnimationData animationData;
    animationData.spritesheetFile = "CharacterWalkAnimation144x16-2.png";
    animationData.frameWidth = 16;
    animationData.frameHeight = 16;
    animationData.startFrame = 0;
    animationData.endFrame = 0;
    animationData.animationSpeed = 5.0f; // Adjust animation speed as needed

    auto animationComponent = std::make_unique<dae::AnimationComponent>(animationData, CharacterObject13.get() , false);
    CharacterObject13->SetLocalPosition(glm::vec3(921.0f, 81.0f, 0.0f));

    //Create HealthComponent and PointComponent
    auto Character1Health3 = std::make_unique<dae::HealthComponent>(100, 3);
    auto Character1points3 = std::make_unique<dae::PointComponent>(0);

    animationComponent->SetRenderScale(2, 2);
    animationComponent->Play();

    HandlePlayerInput(inputManager, CharacterObject13.get(), animationComponent.get());


    //Add HealthComponent and PointComponent to CharacterObject1
    CharacterObject13->AddComponent(std::move(Character1Health3));
    CharacterObject13->AddComponent(std::move(Character1points3));
    CharacterObject13->AddComponent(std::move(animationComponent));

    //CharacterObject13->AddComponent(std::move(CharacterRenderComponent13));

    



    // Create GameObject for displaying lives
    auto livesDisplayObject13 = std::make_unique<dae::GameObject>();
    auto livesDisplayComponent13 = std::make_unique<dae::LivesDisplayComponent>(dae::ResourceManager::GetInstance().LoadFont("arcade-legacy.ttf", 20), *livesDisplayObject13);
    auto character1HealthComponent3 = CharacterObject13->GetComponent<dae::HealthComponent>();
    livesDisplayComponent13->AttachToHealthComponent(character1HealthComponent3);
    livesDisplayObject13->AddComponent(std::move(livesDisplayComponent13));
    livesDisplayObject13->SetLocalPosition(glm::vec3(100, 200, 0.f));

    //Create GameObject for displaying points of Character 1
    auto pointsDisplayObject13 = std::make_unique<dae::GameObject>();
    auto pointsDisplayComponent13 = std::make_unique<dae::PointsDisplayComponent>(dae::ResourceManager::GetInstance().LoadFont("arcade-legacy.ttf", 20), *pointsDisplayObject13); // Assuming a font for displaying points
    auto character1PointComponent3 = CharacterObject13->GetComponent<dae::PointComponent>();
    pointsDisplayComponent13->AttachToPointComponent(character1PointComponent3);
    pointsDisplayObject13->AddComponent(std::move(pointsDisplayComponent13));
    pointsDisplayObject13->SetLocalPosition(glm::vec3(100, 220, 0.f));

    scene->Add(std::move(pointsDisplayObject13));
    scene->Add(std::move(livesDisplayObject13));
    scene->Add(std::move(CharacterObject13));
}


void load()
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
    sound_id soundId = ss.get_sound_id_for_file_path("../Data/04 Lose Life.mp3");

    ss.load_sound(soundId,"../Data/04 Lose Life.mp3");


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