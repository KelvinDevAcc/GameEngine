#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#include "FPSCounterComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"

void load()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

    // Create GameObject for background
    const auto backgroundObject = std::make_shared<dae::GameObject>();
    const auto backgroundRenderComponent = std::make_shared<dae::RenderComponent>();
    backgroundRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.tga"));
    backgroundRenderComponent->SetDimensions(1270, 720);
    backgroundObject->SetLocalPosition(glm::vec3(635, 720, 0.f));
    backgroundObject->AddComponent(backgroundRenderComponent);
    scene.Add(backgroundObject);

    // Create GameObject for logo
    const auto logoObject = std::make_shared<dae::GameObject>();
    const auto logoRenderComponent = std::make_shared<dae::RenderComponent>();
    logoRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.tga"));
    logoObject->SetLocalPosition(glm::vec3(635.f, 360.f, 0.0f));
    logoObject->AddComponent(logoRenderComponent);
    const auto logoRotatorComponent = std::make_shared<dae::RotatorComponent>(10.0f, 635.f, 360.f, 5.0f);
    logoObject->AddComponent(logoRotatorComponent);
    scene.Add(logoObject);

  // Create GameObject for Character 2
    const auto CharacterObject2 = std::make_shared<dae::GameObject>();
    const auto CharacterRenderComponent2 = std::make_shared<dae::RenderComponent>();
    CharacterRenderComponent2->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Character.png"));
    CharacterRenderComponent2->SetDimensions(50, 50);
    CharacterObject2->SetLocalPosition(glm::vec3(360.0f, 500.0f, 0.0f)); // Position of CharacterObject2
    CharacterObject2->AddComponent(CharacterRenderComponent2);
    const auto RotatorComponent2 = std::make_shared<dae::RotatorComponent>(1.5f, CharacterObject2->GetWorldPosition().x, CharacterObject2->GetWorldPosition().y, 50.0f); // Center around local position of CharacterObject2
    CharacterObject2->AddComponent(RotatorComponent2);
    scene.Add(CharacterObject2);

    // Create GameObject for Character 1
    const auto CharacterObject1 = std::make_shared<dae::GameObject>();
    const auto CharacterRenderComponent1 = std::make_shared<dae::RenderComponent>();
    CharacterRenderComponent1->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Character.png"));
    CharacterRenderComponent1->SetDimensions(50, 50);
	CharacterObject1->SetLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    CharacterObject1->AddComponent(CharacterRenderComponent1);
    CharacterObject1->SetParent(CharacterObject2.get(), true); // Set CharacterObject2 as parent
    const auto RotatorComponent1 = std::make_shared<dae::RotatorComponent>(3.0f, CharacterObject1->GetWorldPosition().x, CharacterObject1->GetWorldPosition().y, 50.0f); // Center around (0,0)
    CharacterObject1->AddComponent(RotatorComponent1);
    scene.Add(CharacterObject1);



    // Create GameObject for Title
    const auto TitleObject = std::make_shared<dae::GameObject>();
    const auto to = std::make_shared<dae::TextComponent>("Programming 4 Assignment", font);
    TitleObject->AddComponent(to);
    TitleObject->SetLocalPosition(glm::vec3(635, 20, 0.f));
    scene.Add(TitleObject);

    // Create GameObject for FPS counter
    const auto fpsCounterObject = std::make_shared<dae::GameObject>();
    const auto fpsCounterComponent = std::make_shared<dae::FPSCounterComponent>();
    fpsCounterObject->AddComponent(fpsCounterComponent);

    //// Create TextComponent for displaying FPS
    const auto fpsTextComponent = std::make_shared<dae::TextComponent>("FPS: ", font);
    fpsCounterObject->AddComponent(fpsTextComponent);
    fpsCounterObject->SetLocalPosition(glm::vec3(100.f, 20.f, 0.0f));
    scene.Add(fpsCounterObject);
}

int main(int, char* []) {
    dae::Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}