#include "Commands.h"

#include <iostream>

MoveCommand::MoveCommand(dae::GameObject* gameObject, float deltaX, float deltaY)
    : m_gameObject(gameObject), m_deltaX(deltaX), m_deltaY(deltaY) {}

void MoveCommand::Execute() {
    if (m_gameObject) {
        glm::vec3 currentPosition = m_gameObject->GetLocalPosition();
        currentPosition.x += m_deltaX;
        currentPosition.y += m_deltaY;
        m_gameObject->SetLocalPosition(currentPosition);
    }
}

