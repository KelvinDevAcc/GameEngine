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

void load()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

    // Create GameObject for background
    const auto backgroundObject = std::make_shared<dae::GameObject>();
    const auto backgroundRenderComponent = std::make_shared<dae::RenderComponent>();
    backgroundRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.tga"));
    backgroundRenderComponent->SetDimensions(1270, 720);
    backgroundObject->AddComponent(backgroundRenderComponent);
    backgroundObject->SetPosition(635, 720);
    scene.Add(backgroundObject);

    // Create GameObject for logo
    const auto logoObject = std::make_shared<dae::GameObject>();
    const auto logoRenderComponent = std::make_shared<dae::RenderComponent>();
    logoRenderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.tga"));
    logoObject->AddComponent(logoRenderComponent);
    logoObject->SetPosition(635, 360);
    scene.Add(logoObject);

    // Create GameObject for Title
    const auto TitleObject = std::make_shared<dae::GameObject>();
    const auto to = std::make_shared<dae::TextComponent>("Programming 4 Assignment", font);
    TitleObject->AddComponent(to);
    TitleObject->SetPosition(635, 20);
    scene.Add(TitleObject);

    // Create GameObject for FPS counter
    const auto fpsCounterObject = std::make_shared<dae::GameObject>();
    const auto fpsCounterComponent = std::make_shared<dae::FPSCounterComponent>();
    fpsCounterObject->AddComponent(fpsCounterComponent);

    //// Create TextComponent for displaying FPS
    const auto fpsTextComponent = std::make_shared<dae::TextComponent>("FPS: ", font);
    fpsCounterObject->AddComponent(fpsTextComponent);
    fpsCounterObject->SetPosition(100, 20);
    scene.Add(fpsCounterObject);
}

int main(int, char* []) {
    dae::Minigin engine("../Data/");
    engine.Run(load);
    return 0;
}