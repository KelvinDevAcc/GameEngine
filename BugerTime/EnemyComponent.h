#pragma once
#include "Component.h"
#include "GameObject.h"
#include "SpriteRendererComponent.h"
#include "AnimationComponent.h"
#include "Scene.h"

namespace game {

    class EnemyComponent final : public dae::Component {
    public:
        EnemyComponent(dae::GameObject* owner, dae::Scene* scene);
        ~EnemyComponent() override = default;

        void Update() override;
        void Die();

        std::type_info const& GetComponentType() const override { return typeid(EnemyComponent); }

    private:

        void UpdateAnimation();

        dae::SpriteRendererComponent* m_spriteRenderer;
        dae::AnimationComponent* m_animationComponent;

        dae::GameObject* m_owner;

        dae::Scene* m_scene;

        float m_deathTimer;

        glm::vec3 m_direction;
    };

}
