#pragma once
#include "Component.h"

class BurgerComponent : public dae::Component {
public:
    BurgerComponent(float length, float dropDistance);
    void Update() override;

    std::type_info const& GetComponentType() const override { return typeid(BurgerComponent); }
private:
    bool IsPlayerOverComponent();
    float GetPlayerMovementOverComponent();
    void DropToNextFloor();

    float m_Length;
    float m_DropDistance;
    float m_PlayerWalkedDistance;
    bool m_HasDropped;
};
