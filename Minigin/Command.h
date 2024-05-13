#pragma once
#include "GameObject.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "../BugerTime/Player.h"


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
    MoveCommand(dae::GameObject* gameObject, float deltaX, float deltaY); // Include MovementDirection parameter
    void Execute() override;

private:
    dae::GameObject* m_gameObject;
    float m_deltaX;
    float m_deltaY;
};



class DamageCommand final : public Command {
public:
    DamageCommand(dae::GameObject* gameObject);

    virtual void Execute() override;

private:
    dae::GameObject* m_gameObject;
};



class ScorePointCommand final : public Command {
public:
    ScorePointCommand(dae::GameObject* gameObject);

    virtual void Execute() override;

private:
    dae::GameObject* m_gameObject;
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
