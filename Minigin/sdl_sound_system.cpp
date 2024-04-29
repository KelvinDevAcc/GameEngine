#include "sdl_sound_system.h"


sdl_sound_system::sdl_sound_system() : m_running(true) {
    // Initialize SDL mixer
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG) < 0) {
        std::cerr << "SDL mixer initialization failed: " << Mix_GetError() << std::endl;
        return;
    }

    // Open the audio device
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL audio device opening failed: " << Mix_GetError() << std::endl;
        return;
    }

    m_thread = std::make_unique<std::jthread>([this] { process_events(); });

    dae::EventQueue::AddListener(dae::PlaySoundMessageType::deathSound, this, &sdl_sound_system::onPlaySoundMessage);
}

sdl_sound_system::~sdl_sound_system() {

    stop();
}


void sdl_sound_system::onPlaySoundMessage(const dae::Message& message) {
    try {
        if (message.arguments.size() != 2) {
            std::cerr << "Invalid number of arguments for PlaySound message" << std::endl;
            return;
        }

        const sound_id soundID = std::any_cast<decltype(soundID)>(message.arguments[0]);
        const float volume = std::any_cast<decltype(volume)>(message.arguments[1]);

        play(soundID, volume);
    }
    catch (const std::bad_any_cast& e) {
        std::cerr << "Error extracting arguments from PlaySound message: " << e.what() << std::endl;
    }
}

void sdl_sound_system::play(const sound_id id, const float volume) {
    // Lock the mutex before modifying the sound requests queue
    std::unique_lock<std::mutex> lock(m_sound_requests_mutex);
    m_sound_requests.push({ id, volume }); // Push the sound request to the queue
    lock.unlock(); // Unlock the mutex
    m_sound_requests_cv.notify_one(); // Notify the sound system thread about the new sound request

}

void sdl_sound_system::process_events() {
    while (m_running) {
        // Lock the mutex before accessing the sound requests queue
        std::unique_lock<std::mutex> lock(m_sound_requests_mutex);
        // Wait until there's a sound request or the sound system is stopped
        m_sound_requests_cv.wait(lock, [this] { return !m_sound_requests.empty() || !m_running; });

        if (!m_running) {
            break;
        }

        // Process the first sound request in the queue
        SoundRequest request = m_sound_requests.front();
        m_sound_requests.pop(); 
        lock.unlock(); 

        // Find the music associated with the sound ID
        auto it = m_id_to_music_map.find(request.id);
        if (it == m_id_to_music_map.end()) {
            std::cerr << "Failed to find music for sound ID: " << request.id << std::endl;
            continue; 
        }

        Mix_Music* music = it->second;
        if (!music) {
            std::cerr << "Failed to load music for sounds ID: " << request.id << std::endl;
            continue;
        }

        Mix_VolumeMusic(static_cast<int>(request.volume));
        Mix_PlayMusic(music, 1);
    }

    Mix_CloseAudio();
    Mix_Quit();
}

void sdl_sound_system::stop() {
    // Lock the mutex before modifying the running flag
    std::unique_lock<std::mutex> lock(m_sound_requests_mutex);
    m_running = false; // Set the running flag to false
    lock.unlock(); 
    m_sound_requests_cv.notify_all(); // Notify all waiting threads about the stop signal
    dae::EventQueue::RemoveListener(this);
}

void sdl_sound_system::register_sound_file(const std::string& file_path) {
    // Lock the mutex before modifying the file path to ID map
    std::lock_guard<std::mutex> lock(m_sound_requests_mutex);

    const sound_id new_id = next_sound_id++;

    m_file_path_to_id_map[file_path] = new_id;
}

sound_id sdl_sound_system::get_sound_id_for_file_path(const std::string& file_path) {
    // Lock the mutex before accessing the file path to ID map
    std::lock_guard<std::mutex> lock(m_sound_requests_mutex);

    // Check if the file path exists in the map
    auto it = m_file_path_to_id_map.find(file_path);
    if (it != m_file_path_to_id_map.end()) {
        return it->second; // Return the corresponding ID
    }
    else {
        return 0;
    }
}

void sdl_sound_system::load_sound(sound_id id, const std::string& file_path) {
    // Load the music from the file path using SDL mixer
    if (Mix_Music* music = Mix_LoadMUS(file_path.c_str())) {
        // Lock the mutex before modifying the ID to music map
        std::lock_guard<std::mutex> lock(m_sound_requests_mutex);
        m_id_to_music_map[id] = music; // Store the loaded music with the provided ID
    }
    else {
        std::cerr << "Failed to load music for sound ID: " << id << ". SDL Mixer Error: " << Mix_GetError() << std::endl;
    }
}

void sdl_sound_system::unload_sound(sound_id id) {
    // Lock the mutex before modifying the ID to music map
    std::lock_guard<std::mutex> lock(m_sound_requests_mutex);
    auto it = m_id_to_music_map.find(id);
    if (it != m_id_to_music_map.end()) {
        Mix_FreeMusic(it->second); // Free the memory allocated for the music
        m_id_to_music_map.erase(it); // Remove the entry from the map
    }
}



void logging_sound_system::onPlaySoundMessage(const dae::Message& message)
{
    try {
        // Check if the message has the correct number of arguments
        if (message.arguments.size() != 2) {
            std::cerr << "Invalid number of arguments for PlaySound message" << std::endl;
            return;
        }

        const sound_id soundID = std::any_cast<decltype(soundID)>(message.arguments[0]);
        const float volume = std::any_cast<decltype(volume)>(message.arguments[1]);

        play(soundID, volume);
        std::cout << "playing " << soundID << " at volume " << volume << std::endl;
    }
    catch (const std::bad_any_cast& e) {
        std::cerr << "Error extracting arguments from PlaySound message: " << e.what() << std::endl;
    }
}
