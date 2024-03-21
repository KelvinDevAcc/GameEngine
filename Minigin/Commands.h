#pragma once
#include "Command.h"
#include "GameObject.h"
#include <glm/vec3.hpp>

class MoveCommand : public Command {
public:
    MoveCommand(dae::GameObject* gameObject, float deltaX, float deltaY);

    virtual void Execute() override;

private:
    dae::GameObject* m_gameObject;
    float m_deltaX;
    float m_deltaY;
};
