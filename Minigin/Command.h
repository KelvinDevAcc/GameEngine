#pragma once
#include <string>

#include "AnimationComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PointComponent.h"



class Command 
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};


enum class MovementDirection
{
    None,
    Up,
    Down,
    Left,
    Right
};

class MoveCommand : public Command
{
public:
    MoveCommand(dae::GameObject* gameObject, float deltaX, float deltaY, dae::AnimationComponent* animationComponent); // Include MovementDirection parameter
    void DetermineMovementDirection(float deltaX, float deltaY) const;
    void Execute() override;

private:
    dae::GameObject* m_gameObject;
    float m_deltaX;
    float m_deltaY;
    dae::AnimationComponent* m_animationComponent;
};



class DamageCommand final : public Command {
public:
    DamageCommand(dae::GameObject* gameObject, int damageAmount);

    virtual void Execute() override;

private:
    dae::HealthComponent* m_healthComponent{};
    dae::GameObject* m_gameObject;
    int m_damageAmount;
};



class ScorePointCommand final : public Command {
public:
    ScorePointCommand(dae::GameObject* gameObject, int scoreAmount);

    virtual void Execute() override;

private:
    dae::PointComponent* m_pointComponent{};
    dae::GameObject* m_gameObject;
    int m_scoreAmount;
};

class GoToNextSceneCommand final : public Command {
public:
    GoToNextSceneCommand();

    virtual void Execute() override;
};


class PlaySoundCommand : public Command {
public:
    PlaySoundCommand();
    void Execute() override;

};
