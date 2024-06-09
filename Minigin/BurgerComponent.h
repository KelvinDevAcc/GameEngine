#pragma once
#include "Component.h"

class BurgerComponent : public dae::Component {
public:
    BurgerComponent(float length, float dropDistance);
    void Update() override;

    void StartDropping();
    bool GetFalling() { return m_IsDropping; }

    std::type_info const& GetComponentType() const override { return typeid(BurgerComponent); }
private:
    bool IsPlayerOverComponent();
    float GetPlayerMovementOverComponent() const;
    void DropToNextFloor();

    dae::GameObject* m_DroppingPlayer;
    bool m_IsDropping;
    float m_Length;
    float m_DropDistance;
    float m_PlayerWalkedDistance;
    bool m_HasDropped;
};
