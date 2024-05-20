#include "SceneHelpers.h"
#include <ostream>
#include "ResourceManager.h"
#include "SceneData.h"
#include "SpriteRendererComponent.h"
#include "../BugerTime/Player.h"


void SceneHelpers::CreateFloor(dae::Scene* scene, float x, float y, glm::vec2 scale) {
    auto floorObject = std::make_unique<dae::GameObject>();
    auto spriteRenderer = std::make_unique<dae::SpriteRendererComponent>(floorObject.get(), dae::ResourceManager::GetSprite("floor"));
    spriteRenderer->SetDimensions(scale.x, scale.y);
    floorObject->AddComponent(std::move(spriteRenderer));
    floorObject->SetLocalPosition(glm::vec3(x, y, 0.0f));

    auto hitBox = std::make_unique<HitBox>(scale);
    hitBox->SetGameObject(floorObject.get());
    floorObject->AddComponent(std::move(hitBox));

    dae::SceneData::GetInstance().AddGameObject(floorObject.get(), dae::GameObjectType::Floor);


    scene->Add(std::move(floorObject));
}

void SceneHelpers::CreateLadder(dae::Scene* scene, float x, float y, bool isUp, glm::vec2 scale) {
    auto ladderObject = std::make_unique<dae::GameObject>();
    const std::string spriteName = isUp ? "ladder_up" : "ladder_down";
    auto spriteRenderer = std::make_unique<dae::SpriteRendererComponent>(ladderObject.get(), dae::ResourceManager::GetSprite(spriteName));
    spriteRenderer->SetDimensions(scale.x, scale.y);
    ladderObject->AddComponent(std::move(spriteRenderer));
    ladderObject->SetLocalPosition(glm::vec3(x, y, 0.0f));

    auto hitBox = std::make_unique<HitBox>(scale);
    hitBox->SetGameObject(ladderObject.get());
    ladderObject->AddComponent(std::move(hitBox));

    dae::SceneData::GetInstance().AddGameObject(ladderObject.get(), dae::GameObjectType::Ladder);

    scene->Add(std::move(ladderObject));
}

void SceneHelpers::CreateSolidLadder(dae::Scene* scene, float x, float y, glm::vec2 scale) {
    auto solidLadderObject = std::make_unique<dae::GameObject>();
    auto spriteRenderer = std::make_unique<dae::SpriteRendererComponent>(solidLadderObject.get(), dae::ResourceManager::GetSprite("stairs"));
    spriteRenderer->SetDimensions(scale.x, scale.y);
    solidLadderObject->AddComponent(std::move(spriteRenderer));
    solidLadderObject->SetLocalPosition(glm::vec3(x, y, 0.0f));

    auto hitBox = std::make_unique<HitBox>(scale);
    hitBox->SetGameObject(solidLadderObject.get());
    solidLadderObject->AddComponent(std::move(hitBox));

    dae::SceneData::GetInstance().AddGameObject(solidLadderObject.get(), dae::GameObjectType::SolidLadder);

    scene->Add(std::move(solidLadderObject));
}

void SceneHelpers::CreatePlatformLeft(dae::Scene* scene, float x, float y, glm::vec2 scale) {
    // Create the left part of the platform
    auto leftObject = std::make_unique<dae::GameObject>();
    auto leftSpriteRenderer = std::make_unique<dae::SpriteRendererComponent>(leftObject.get(), dae::ResourceManager::GetSprite("left_basket"));
    leftSpriteRenderer->SetDimensions(scale.x, scale.y);
    leftObject->AddComponent(std::move(leftSpriteRenderer));
    leftObject->SetLocalPosition(glm::vec3(x, y, 0.0f));

    auto hitBox = std::make_unique<HitBox>(scale);
    hitBox->SetGameObject(leftObject.get());
    leftObject->AddComponent(std::move(hitBox));

    dae::SceneData::GetInstance().AddGameObject(leftObject.get(), dae::GameObjectType::PlatformLeft);

    scene->Add(std::move(leftObject));
}

void SceneHelpers::CreatePlatformCombined(dae::Scene* scene, float x, float y, glm::vec2 scale) {
    // Create the left part of the platform
    auto combinedObject = std::make_unique<dae::GameObject>();
    auto leftSpriteRenderer = std::make_unique<dae::SpriteRendererComponent>(combinedObject.get(), dae::ResourceManager::GetSprite("combined_basket"));
    leftSpriteRenderer->SetDimensions(scale.x, scale.y);
    combinedObject->AddComponent(std::move(leftSpriteRenderer));
    combinedObject->SetLocalPosition(glm::vec3(x, y, 0.0f));

    auto hitBox = std::make_unique<HitBox>(scale);
    hitBox->SetGameObject(combinedObject.get());
    combinedObject->AddComponent(std::move(hitBox));

    dae::SceneData::GetInstance().AddGameObject(combinedObject.get(), dae::GameObjectType::PlatformCombined);

    scene->Add(std::move(combinedObject));
}

void SceneHelpers::CreatePlatformMiddle(dae::Scene* scene, float x, float y, glm::vec2 scale) {

    // Create the middle part of the platform
    auto midObject = std::make_unique<dae::GameObject>();
    auto midSpriteRenderer = std::make_unique<dae::SpriteRendererComponent>(midObject.get(), dae::ResourceManager::GetSprite("mid_basket"));
    midSpriteRenderer->SetDimensions(scale.x, scale.y);
    midObject->AddComponent(std::move(midSpriteRenderer));
    midObject->SetLocalPosition(glm::vec3(x, y, 0.0f));

    auto hitBox = std::make_unique<HitBox>(scale);
    hitBox->SetGameObject(midObject.get());
    midObject->AddComponent(std::move(hitBox));

    dae::SceneData::GetInstance().AddGameObject(midObject.get(), dae::GameObjectType::PlatformMiddle);

    scene->Add(std::move(midObject));
}

void SceneHelpers::CreatePlatformRight(dae::Scene* scene, float x, float y, glm::vec2 scale) {

    // Create the right part of the platform
    auto rightObject = std::make_unique<dae::GameObject>();
    auto rightSpriteRenderer = std::make_unique<dae::SpriteRendererComponent>(rightObject.get(), dae::ResourceManager::GetSprite("right_basket"));
    rightSpriteRenderer->SetDimensions(scale.x, scale.y);
    rightObject->AddComponent(std::move(rightSpriteRenderer));
    rightObject->SetLocalPosition(glm::vec3(x, y, 0.0f));

    auto hitBox = std::make_unique<HitBox>(scale);
    hitBox->SetGameObject(rightObject.get());
    rightObject->AddComponent(std::move(hitBox));

    dae::SceneData::GetInstance().AddGameObject(rightObject.get(), dae::GameObjectType::PlatformRight);

    scene->Add(std::move(rightObject));
}



void SceneHelpers::LoadMapIntoScene(const LoadMap& loadMap, dae::Scene* scene, const glm::vec3& startPos, glm::vec2 scale) {
    const auto& map = loadMap.getMap();

    // Initialize variables to store the maximum X and Y coordinates

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            const char tile = map[y][x];
            const float posX = startPos.x + x * scale.x;
            const float posY = startPos.y + y * scale.y;

            switch (tile) {
            case 'v':
                CreateLadder(scene, posX, posY, false, scale);
                break;
            case '#':
                CreateSolidLadder(scene, posX, posY, scale);
                break;
            case '^':
                CreateLadder(scene, posX, posY, true, scale);
                break;
            case '|':
                CreateLadder(scene, posX, posY, true, scale);
                break;
            case '_':
                CreateFloor(scene, posX, posY, scale);
                break;
            case 'u':
                CreatePlatformMiddle(scene, posX, posY, scale);
                break;
            case 'l':
                CreatePlatformLeft(scene, posX, posY, scale);
                break;
            case 'r':
                CreatePlatformRight(scene, posX, posY, scale);
                break;
            case 'c':
                CreatePlatformCombined(scene, posX, posY, scale);
                break;
            default:
                break;
            }
        }
    }
}




