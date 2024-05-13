#pragma once

namespace game
{
    class Player;

    class PlayerState
    {
    public:
        virtual ~PlayerState() = default;

        PlayerState(PlayerState&&) = delete;
        PlayerState(const PlayerState&) = delete;
        PlayerState& operator=(PlayerState&&) = delete;
        PlayerState& operator=(const PlayerState&) = delete;

        virtual void OnEnterState(Player& /*player*/) {}
        virtual void Update(Player& /*player*/) {}
        virtual void OnExitState(Player& /*player*/) {}

    protected:
        PlayerState() = default;
    };

    class PlayerWalkingState final : public PlayerState
    {
    public:

        void OnEnterState(Player& player) override;
        void Update(Player& player) override;
        void OnExitState(Player& player) override;
    };

    class PlayerAttackingState final : public PlayerState
    {
    public:
        void OnEnterState(Player& player) override;
        void Update(Player& player) override;
        void OnExitState(Player& player) override;
    };

    class PlayerDyingState final : public PlayerState
    {
    public:
        void OnEnterState(Player& player) override;
        void Update(Player& player) override;
        void OnExitState(Player& player) override;
    };

    class PlayerIdleState final : public PlayerState
    {
    public:
        void OnEnterState(Player& player) override;
        void Update(Player& player) override;
        void OnExitState(Player& player) override;
    };
}