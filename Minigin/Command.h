#pragma once

#include "GameObject.h"
#include "HealthComponent.h"
#include "MenuComponent.h"
#include "PointComponent.h"
#include "SceneManager.h"
#include "SelectNameComponent.h"
#include "sound_system.h"
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
    MoveCommand(int playerNumber ,float deltaX, float deltaY); // Include MovementDirection parameter
    void Execute() override;

private:
    dae::GameObject* m_gameObject;
    float m_deltaX;
    float m_deltaY;
    int m_playernum;
};



class DamageCommand final : public Command {
public:
    DamageCommand(int playerNumber);

    virtual void Execute() override;

private:
    dae::GameObject* m_gameObject;
};



class ScorePointCommand final : public Command {
public:
    ScorePointCommand(int playerNumber);

    virtual void Execute() override;

private:
    dae::GameObject* m_gameObject;
};

class GoToNextSceneCommand final : public Command {
public:
    GoToNextSceneCommand();

    virtual void Execute() override;
};



//sound Commands
class PlaySoundCommand : public Command {
public:
    PlaySoundCommand();
    void Execute() override;

};


class MuteCommand : public Command {
public:
    explicit MuteCommand(sound_system* soundSystem);
    void Execute() override;

private:
    sound_system* m_soundSystem;
};

class IncreaseVolumeCommand : public Command {
public:
    explicit IncreaseVolumeCommand(sound_system* soundSystem);
    void Execute() override;

private:
    sound_system* m_soundSystem;
};

class DecreaseVolumeCommand : public Command {
public:
    explicit DecreaseVolumeCommand(sound_system* soundSystem);
    void Execute() override;

private:
    sound_system* m_soundSystem;
};


//Menu Commands 
class NavigateUpCommand : public Command
{
public:
    void Execute() override;

private:
    static dae::MenuComponent* FindMenuComponent();
};

class NavigateDownCommand : public Command
{
public:
    void Execute() override;

private:
    static dae::MenuComponent* FindMenuComponent();
};

class SelectOptionCommand : public Command
{
public:
    void Execute() override;

private:
    static dae::MenuComponent* FindMenuComponent();
};


//select name commands

class NavigateUpLetterCommand : public Command
{
public:
    void Execute() override;

private:
    static SelectNameComponent* FindSelectNameComponent();
};

class NavigateDownLetterCommand : public Command
{
public:
    void Execute() override;

private:
    static SelectNameComponent* FindSelectNameComponent();
};

class SelectOptionLetterCommand : public Command
{
public:
    void Execute() override;

private:
    static SelectNameComponent* FindSelectNameComponent();
};

class saveScoreCommand : public Command
{
public:
    void Execute() override;

private:
    static SelectNameComponent* FindSelectNameComponent();

    std::string m_currentname;

};