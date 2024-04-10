#pragma once
#include "Component.h"
#include "GameObject.h"


namespace dae
{
    class RotatorComponent : public Component
    {
    public:
        RotatorComponent(float rotationSpeed, float centerX, float centerY, float radius);

        void Update() override;
        

        const char* GetComponentType() const override { return "RotatorComponent"; }

    private:
        float m_RotationSpeed; // Rotation speed in degrees per second
        float m_CurrentRotation; // Current rotation angle
        float m_CenterX;
        float m_CenterY;
        float m_Radius;
    };
}

