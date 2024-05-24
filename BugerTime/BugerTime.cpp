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
#include "HitBox.h"
#include "LivesDisplayComponent.h"
#include "LoadMap.h"
#include "Player.h"
#include "PointsDisplayComponent.h"
#include "RotatorComponent.h"
#include "SceneData.h"
#include "SceneHelpers.h"
#include "sdl_sound_system.h"
#include "servicelocator.h"

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
    ss.register_sound_file("../Data/Sounds/2.mp3");
    ss.register_sound_file("../Data/Sounds/04 Lose Life.mp3");

    // Get the ID for the sound file path
    const sound_id soundId = ss.get_sound_id_for_file_path("../Data/Sounds/04 Lose Life.mp3");
    ss.setVolume(50.f);
    ss.load_sound(soundId, "../Data/Sounds/04 Lose Life.mp3");


	dae::ResourceManager::LoadFont("Lingua", "Lingua.otf", 36);
	dae::ResourceManager::LoadFont("Linguasmall", "Lingua.otf", 26);
	dae::ResourceManager::LoadFont("arcade", "arcade-legacy.ttf", 20);
	dae::ResourceManager::LoadFont("arcadeBig", "arcade-legacy.ttf", 40);
	dae::ResourceManager::LoadFont("PressStart", "PressStart2P-vaV7.ttf", 20);

	dae::ResourceManager::LoadSprite("background", "background.tga");
	dae::ResourceManager::LoadSprite("logo", "logo.tga");

	dae::ResourceManager::LoadSprite("Stage01", "Stage01.png");

    dae::ResourceManager::LoadSprite("floor", "floor.png");
    dae::ResourceManager::LoadSprite("ladder_down", "go_down.png");
    dae::ResourceManager::LoadSprite("ladder_up", "go_up.png");
    dae::ResourceManager::LoadSprite("stairs", "stairs.png");
    dae::ResourceManager::LoadSprite("right_basket", "right_basket.png");
    dae::ResourceManager::LoadSprite("mid_basket", "mid_basket.png");
    dae::ResourceManager::LoadSprite("left_basket", "left_basket.png");
    dae::ResourceManager::LoadSprite("combined_basket", "combined_basket.png");


    dae::ResourceManager::LoadSprite("Bugertop", "Bugertop.png");
    dae::ResourceManager::LoadSprite("cheese", "cheese.png");
    dae::ResourceManager::LoadSprite("Meat", "Meat.png");
    dae::ResourceManager::LoadSprite("tomato", "tomato.png");
    dae::ResourceManager::LoadSprite("lettuce", "lettuce.png");
    dae::ResourceManager::LoadSprite("Buger_bottom", "Buger_bottom.png");


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
            { "Attacking", { { { 1, 1 } }, 1 } },
            { "Victory", { { { 3, 1 }, { 1, 0 }}, 3 } }

        });
    dae::ResourceManager::LoadSprite("egg",
        "Arcade - Burger Time - Characters & Objects-white.png",
        11,  // rowCount
        15,  // colCount
        {
            { "Idle", { { { 1, 6 },{ 1, 6 }}, 1 } },
            { "Walk_Right", { { { 2, 6 }, { 3, 6 } }, 2 } },
            { "Walk_Left", { { { 2, 6 }, { 3, 6 } }, 2 } },
            { "Walk_Up", { { { 4, 6 }, { 5, 6 } }, 2 } },
            { "Walk_Down", { { { 0, 6 }, { 1, 6 } }, 2 } },
            { "Dying", { { { 0, 7 }, { 1, 7 }, { 2, 7 }, { 3, 7 } }, 1 } },
            { "Stunned", { { { 4, 7 }, { 5, 7 } }, 1 } }
        });
    dae::ResourceManager::LoadSprite("sausage",
        "Arcade - Burger Time - Characters & Objects-white.png",
        11,  // rowCount
        15,  // colCount
        {
            { "Idle", { { { 1, 2 }}, 1 } },
            { "Walk_Right", { { { 2, 2 }, { 3, 2 } }, 2 } },
            { "Walk_Left", { { { 2, 2 }, { 3, 2 } }, 2 } },
            { "Walk_Up", { { { 4, 2 }, { 5, 2 } }, 2 } },
            { "Walk_Down", { { { 0, 2 }, { 1, 2 } }, 2 } },
            { "Dying", { { { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 } }, 1 } },
            { "Stunned", { { { 4, 3 }, { 5, 3 } }, 1 } }
        });
    dae::ResourceManager::LoadSprite("Pickle",
        "Arcade - Burger Time - Characters & Objects-white.png",
        11,  // rowCount
        15,  // colCount
        {
            { "PickleIdle", { { { 1, 4 }}, 1 } },
            { "PickleWalk_Right", { { { 2, 4 }, { 3, 4 } }, 2 } },
            { "PickleWalk_Left", { { { 2, 4 }, { 3, 4 } }, 2 } },
            { "PickleWalk_Up", { { { 4, 4 }, { 5, 4 } }, 2 } },
            { "PickleWalk_Down", { { { 0, 4 }, { 1, 4 } }, 2 } },
            { "PickleDying", { { { 0, 5 }, { 1, 5 }, { 2, 5 }, { 3, 5 } }, 1 } },
            { "PickleStunned", { { { 4, 5 }, { 5, 5 } }, 1 } }
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


}

void BindMenuCommands(dae::MenuComponent* menu, const dae::InputManager& inputManager)
{
    // Assuming SDL_SCANCODE_W is for moving up, SDL_SCANCODE_S for moving down, and SDL_SCANCODE_RETURN for selecting
    inputManager.BindCommand(SDL_SCANCODE_I, KeyState::Up, std::make_unique<NavigateUpCommand>(menu), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_K, KeyState::Up, std::make_unique<NavigateDownCommand>(menu), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_L, KeyState::Up, std::make_unique<SelectOptionCommand>(menu), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_M, KeyState::Up, std::make_unique<GoToNextSceneCommand>(), InputType::Keyboard);

	inputManager.BindCommand(SDL_SCANCODE_G, KeyState::Up, std::make_unique<MuteCommand>(&servicelocator::get_sound_system()), InputType::Keyboard);
	inputManager.BindCommand(SDL_SCANCODE_P, KeyState::Up, std::make_unique<PlaySoundCommand>(), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_MINUS, KeyState::Up, std::make_unique<DecreaseVolumeCommand>(&servicelocator::get_sound_system()), InputType::Keyboard);
    inputManager.BindCommand(SDL_SCANCODE_EQUALS, KeyState::Up, std::make_unique<IncreaseVolumeCommand>(&servicelocator::get_sound_system()), InputType::Keyboard);

    // Add similar bindings for controller if needed
}
void UnBindMenuCommands(const dae::InputManager& inputManager)
{
    // Assuming SDL_SCANCODE_W is for moving up, SDL_SCANCODE_S for moving down, and SDL_SCANCODE_RETURN for selecting
    inputManager.UnbindCommand(SDL_SCANCODE_I, KeyState::Up,InputType::Keyboard);
    inputManager.UnbindCommand(SDL_SCANCODE_K, KeyState::Up, InputType::Keyboard);
    inputManager.UnbindCommand(SDL_SCANCODE_L, KeyState::Up, InputType::Keyboard);
    inputManager.UnbindCommand(SDL_SCANCODE_M, KeyState::Up,  InputType::Keyboard);
    inputManager.UnbindCommand(SDL_SCANCODE_P, KeyState::Up, InputType::Keyboard);

    // Add similar bindings for controller if needed
}

void LoadStartMenu()
{
    auto& sceneManager = dae::SceneManager::GetInstance();
    const auto& inputManager = dae::InputManager::GetInstance();
    const auto startMenuScene = sceneManager.CreateScene("StartMenu");

    std::vector<std::string> options = { "single player", "multiplayer", "versus Mode" };
    std::vector<std::function<void()>> callbacks =
    {
        [inputManagerPtr = &inputManager]() { dae::SceneManager::GetInstance().SetActiveScene("Scene4"); UnBindMenuCommands(*inputManagerPtr); },  // Example: Load single player scene
        []() { dae::SceneManager::GetInstance().SetActiveScene("Scene5"); },  // Example: Load multiplayer scene
        []() { dae::SceneManager::GetInstance().SetActiveScene("Scene6"); }   // Example: Load versus mode scene
    };

    // Create the GameObject for the menu
    auto menuObject = std::make_unique<dae::GameObject>();
    menuObject->SetLocalPosition(glm::vec3(635, 300, 0.f));
    auto menuComponent = std::make_unique<dae::MenuComponent>(menuObject.get(), options, callbacks, dae::ResourceManager::GetFont("arcadeBig"), 70.0f);
    menuComponent->SetTextColor(SDL_Color{ 220,100,100,255 });
    BindMenuCommands(menuComponent.get(), inputManager);
    menuObject->AddComponent(std::move(menuComponent));

    // Add the menu GameObject to the scene
    startMenuScene->Add(std::move(menuObject));


    // Create GameObject for Title
    auto TitleObject02 = std::make_unique<dae::GameObject>();
    auto titleTextComponent02 = std::make_unique<dae::TextComponent>("BURGERTIME", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 255, 0, 0, 255 }, *TitleObject02); // Pass the GameObject reference here
    TitleObject02->SetLocalPosition(glm::vec3(635, 70, 0.f));
    TitleObject02->AddComponent(std::move(titleTextComponent02));
    startMenuScene->Add(std::move(TitleObject02));

    auto Infocharacter1Txt02 = std::make_unique<dae::GameObject>();
    auto character1textcomponent02 = std::make_unique<dae::TextComponent>("@ CORP 1982 DATA EAST INC", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 255, 0, 0, 255 }, *Infocharacter1Txt02); // Specify color here
    Infocharacter1Txt02->AddComponent(std::move(character1textcomponent02));
    Infocharacter1Txt02->SetLocalPosition(glm::vec3(635, 140, 0.f));
    startMenuScene->Add(std::move(Infocharacter1Txt02));

    auto Infocharacter2Txt02 = std::make_unique<dae::GameObject>();
    auto character2textcomponent02 = std::make_unique<dae::TextComponent>("MFGD BY BALLY MIDWAY MFG, CO,", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 255, 0, 0, 255 }, *Infocharacter2Txt02); // Specify color here
    Infocharacter2Txt02->AddComponent(std::move(character2textcomponent02));
    Infocharacter2Txt02->SetLocalPosition(glm::vec3(635, 170, 0.f));
    startMenuScene->Add(std::move(Infocharacter2Txt02));
}


void Scene2(dae::Scene* scene)
{

    //// Create GameObject for FPS counter
    //auto fpsCounterObject1 = std::make_unique<dae::GameObject>();
    //auto fpsTextComponent1 = std::make_unique<dae::TextComponent>("FPS: ", dae::ResourceManager::GetFont("Lingua"), SDL_Color{ 252, 157, 3, 255 }, *fpsCounterObject1); // Specify color here
    //auto fpsCounterComponent1 = std::make_unique<dae::FPSCounterComponent>(fpsTextComponent1.get());
    //fpsCounterObject1->SetLocalPosition(glm::vec3(100.f, 20.f, 0.0f));
    //fpsCounterObject1->AddComponent(std::move(fpsTextComponent1));
    //fpsCounterObject1->AddComponent(std::move(fpsCounterComponent1));
    //scene->Add(std::move(fpsCounterObject1));


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


void Scene4(dae::Scene* scene, const dae::InputManager& inputManager)
{
    //// Create GameObject for background
    //auto backgroundObject03 = std::make_unique<dae::GameObject>();
    //auto backgroundRenderComponent03 = std::make_unique<dae::SpriteRendererComponent>(backgroundObject03.get(), dae::ResourceManager::GetSprite("Stage01"));
    //backgroundRenderComponent03->SetDimensions(624, 600);
    //backgroundObject03->SetLocalPosition(glm::vec3(635, 360, 0.f));
    //backgroundObject03->AddComponent(std::move(backgroundRenderComponent03));
    //scene->Add(std::move(backgroundObject03));
    // Load the map
    constexpr glm::vec3 startPos(335, 20, 0.0f);
    constexpr glm::vec2 Mapscale(40, 29.5f);

    const LoadMap loadMap("../Data/maps/map1.map", "../Data/maps/map1.ingmap");
    SceneHelpers::LoadMapIntoScene(loadMap, scene, startPos, Mapscale);

    SceneHelpers::LoadIngMapIntoScene(loadMap, scene, startPos, Mapscale);


    //Create GameObject for Character 1
    auto CharacterObject1 = std::make_unique<dae::GameObject>();

    auto hitBox = std::make_unique<HitBox>(glm::vec2(20, 40));
    hitBox->SetGameObject(CharacterObject1.get());
    CharacterObject1->AddComponent(std::move(hitBox));

    // Create and set up SpriteRendererComponent component
    auto spriterenderComponent = std::make_unique<dae::SpriteRendererComponent>(CharacterObject1.get(), dae::ResourceManager::GetSprite("chef"), glm::ivec2{ 0,0 });
    spriterenderComponent->SetDimensions(40, 40);
    CharacterObject1->AddComponent(std::move(spriterenderComponent));

    // Create and set up AnimationComponent component
    auto animationComponent = std::make_unique<dae::AnimationComponent>(CharacterObject1.get(), CharacterObject1->GetComponent<dae::SpriteRendererComponent>(), "Idle");
    CharacterObject1->AddComponent(std::move(animationComponent));

    auto Character1Health = std::make_unique<dae::HealthComponent>(100, 3);
    auto Character1points = std::make_unique<dae::PointComponent>(0);

    CharacterObject1->AddComponent(std::move(Character1Health));
    CharacterObject1->AddComponent(std::move(Character1points));

    CharacterObject1->SetLocalPosition(glm::vec3(895.5f, 500.0f, 0.0f));

    auto PlayerComponent = std::make_unique<game::Player>(CharacterObject1.get());
    PlayerComponent->SetMap(loadMap);
    CharacterObject1->AddComponent(std::move(PlayerComponent));


    HandlePlayerInput(inputManager, CharacterObject1.get());

    dae::SceneData::GetInstance().AddGameObject(CharacterObject1.get(), dae::GameObjectType::Player);

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



}

void Scene5(dae::Scene* scene)
{
    constexpr glm::vec3 startPos(335, 50, 0.0f);
    constexpr glm::vec2 Mapscale(35, 25.5f);

    const LoadMap loadMap("../Data/maps/map2.map", "../Data/maps/map2.ingmap");
    SceneHelpers::LoadMapIntoScene(loadMap, scene, startPos, Mapscale);

    SceneHelpers::LoadIngMapIntoScene(loadMap, scene, startPos, Mapscale);
	
}

void Scene6(dae::Scene* scene)
{
    constexpr glm::vec3 startPos(335, 50, 0.0f);
    constexpr glm::vec2 Mapscale(35, 25.5f);

    const LoadMap loadMap("../Data/maps/map3.map", "../Data/maps/map3.ingmap");
    SceneHelpers::LoadMapIntoScene(loadMap, scene, startPos, Mapscale);

    SceneHelpers::LoadIngMapIntoScene(loadMap, scene, startPos, Mapscale);

}

void load()
{
    LoadResources();
    LoadStartMenu();

    auto& sceneManager = dae::SceneManager::GetInstance();
    const auto& inputManager = dae::InputManager::GetInstance();

    const auto& scene2 = sceneManager.CreateScene("Scene2");
    const auto& scene4 = sceneManager.CreateScene("Scene4");
    const auto& scene5 = sceneManager.CreateScene("Scene5");
    const auto& scene6 = sceneManager.CreateScene("Scene6");


    //Scene1(inputManager, scene);
    Scene2(scene2);
    //Scene3(inputManager, scene3);
    Scene4(scene4, inputManager);
    Scene5(scene5);
    Scene6(scene6);

    sceneManager.SetActiveScene("StartMenu");

}

int main(int, char* []) {
    dae::Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}