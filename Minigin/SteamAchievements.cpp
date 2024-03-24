#include "SteamAchievements.h"

#include <iostream>
#include <isteamuserstats.h>


void dae::SteamAchievements::Update(float /*deltaTime*/)
{
}

void dae::SteamAchievements::UpdateObsever(GameEvent event)
{
    switch (event)
    {

    case GameEvent::ScoredWinningpoints:
        SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
        break;
    case GameEvent::playerDied:
        SteamUserStats()->SetAchievement("ACH_TRAVEL_FAR_ACCUM");
        break;
    }


    bool success = SteamUserStats()->StoreStats();
    if (success)
        std::cout << "Achievement Unlocked: " << (int)event << std::endl;
    else
        std::cout << "Failed to unlock achievement: " << (int)event << std::endl;

}

