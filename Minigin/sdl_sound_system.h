#pragma once

#include <iostream>
#include <memory>
#include <ostream>
#include <SDL.h>

#include "sound_system.h"
#include <SDL_mixer.h>

class sdl_sound_system final : public sound_system
{
public:
    void play(const sound_id id, const float volume) override {

        if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG) < 0) {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        }

        // Open the audio device
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("SDL_mixer could not open audio! SDL_mixer Error: %s\n", Mix_GetError());
        }
        // Load the music (MP3) file
        Mix_Music* music = Mix_LoadMUS("../Data/02 Main Theme.mp3");

        if (music != nullptr) {
            // Set the music volume
            Mix_VolumeMusic(static_cast<int>(volume * MIX_MAX_VOLUME));

            // Play the music
            if (Mix_PlayMusic(music, 0) == -1) {
                std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
            }
        }
        else {
            std::cerr << "Failed to load music for ID: " << id << std::endl;
        }
    }

};

class logging_sound_system final : public sound_system {
    std::unique_ptr<sound_system> _real_ss;
public:
    logging_sound_system(std::unique_ptr<sound_system>&& ss) : _real_ss(std::move(ss)) {}
    ~logging_sound_system() override = default;
    void play(const sound_id id, const float volume) override {
        _real_ss->play(id, volume);
        std::cout << "playing " << id << " at volume " << volume << std::endl;
    }
};