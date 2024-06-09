#pragma once
#include "AnimationComponent.h"
#include "HitBox.h"

class Pepper : public dae::Component
{
public:
    Pepper(dae::GameObject* owner, const glm::vec3& direction, float speed, float lifetime);

    void Update() override;
    void Render() const override;

    void Activate();
    void Deactivate();

    const std::type_info& GetComponentType() const override { return typeid(Pepper); }

private:
    glm::vec3 m_Direction;
    float m_Speed;
    float m_Lifetime;
    bool m_IsActive;
    HitBox* m_HitBox;
    dae::AnimationComponent* m_AnimationComponent;

    dae::GameObject* m_owner;

    std::unique_ptr<dae::GameObject> m_PerperObject;
};

