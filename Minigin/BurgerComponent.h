#pragma once
#include "Component.h"

class BurgerComponent : public dae::Component {
public:
    BurgerComponent(float length, float dropDistance);
    void Update() override;

    std::type_info const& GetComponentType() const override { return typeid(BurgerComponent); }
private:
    bool IsPlayerOverComponent() const;
    float GetPlayerMovementOverComponent() const;
    void DropToNextFloor();

    bool m_IsDropping;
    float m_Length;
    float m_DropDistance;
    float m_PlayerWalkedDistance;
    bool m_HasDropped;
};
