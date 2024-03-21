#pragma once
#include "GameObject.h"
#include "HealthComponent.h"
#include "PointComponent.h"



class Command 
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};


class MoveCommand final : public Command {
public:
    MoveCommand(dae::GameObject* gameObject, float deltaX, float deltaY);

    virtual void Execute() override;

private:
    dae::GameObject* m_gameObject;
    float m_deltaX;
    float m_deltaY;
};



class DamageCommand final : public Command {
public:
    DamageCommand(dae::HealthComponent* healthComponent, int damageAmount);

    virtual void Execute() override;

private:
    dae::HealthComponent* m_healthComponent;
    int m_damageAmount;
};



class ScorePointCommand final : public Command {
public:
    ScorePointCommand(dae::PointComponent* pointComponent, int scoreAmount);

    virtual void Execute() override;

private:
    dae::PointComponent* m_pointComponent;
    int m_scoreAmount;
};