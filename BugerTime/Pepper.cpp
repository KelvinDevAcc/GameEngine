#include "Pepper.h"
#include "GameObject.h"
#include "GameTime.h"
#include "SceneData.h"
#include <iostream>

#include "ResourceManager.h"

Pepper::Pepper(dae::GameObject* owner, const glm::vec3& direction, float speed, float lifetime)
	: m_Direction(direction), m_Speed(speed), m_Lifetime(lifetime), m_IsActive(false), m_HitBox(nullptr),
	  m_AnimationComponent(nullptr), m_owner(owner)
{
		//float yPos = m_owner->GetWorldPosition().y;
		auto PeperObject = std::make_unique<dae::GameObject>();
        auto spriterenderComponent = std::make_unique<dae::SpriteRendererComponent>(PeperObject.get(), dae::ResourceManager::GetSprite("sausage"));
        spriterenderComponent->SetDimensions(40, 40);
        PeperObject->AddComponent(std::move(spriterenderComponent));

        auto animationComponent = std::make_unique<dae::AnimationComponent>(PeperObject.get(), PeperObject->GetComponent<dae::SpriteRendererComponent>(), "Walk_Right");
        //animationComponent->Play("Walk_Right", true);
        m_AnimationComponent = animationComponent.get();
        PeperObject->AddComponent(std::move(animationComponent));


        auto  hitBox = std::make_unique<HitBox>(glm::vec2(m_owner->GetDimensions().first, m_owner->GetDimensions().second));
		PeperObject->AddComponent(std::move(hitBox));
		// Adjust the y-coordinate of the local position based on the parent's position
        PeperObject->SetLocalPosition(glm::vec3(100, 100, 0.f));

        //PeperObject->SetParent(m_owner);
        m_PerperObject = std::move(PeperObject);
}

void Pepper::Update()
{
   /* if (!m_IsActive)
        return;*/

    if (!m_HitBox)
    {
        m_HitBox = m_PerperObject->GetComponent<HitBox>();
        if (!m_HitBox)
        {
            std::cerr << "Error: Pepper Attack HitBox is nullptr\n";
            return;
        }
    }

    m_PerperObject->Update();

    m_Lifetime -= dae::GameTime::GetDeltaTime();
    if (m_Lifetime <= 0.0f)
    {
        Deactivate();
    }
}

void Pepper::Render() const
{
  /*  if (!m_IsActive)
        return;*/

    m_PerperObject->Render();
}

void Pepper::Activate()
{
   // m_IsActive = true;
    m_Lifetime = 1.0f; // Reset lifetime
    m_AnimationComponent->Play("Walk_Right", true);
}

void Pepper::Deactivate()
{
    m_IsActive = false;
}

  