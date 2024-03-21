#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#include "FPSCounterComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "GameObject.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1270,
		720,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	const auto& renderer = Renderer::GetInstance();
	const auto& sceneManager = SceneManager::GetInstance();
	const auto& input = InputManager::GetInstance();

	auto lastTime = std::chrono::high_resolution_clock::now();
	constexpr auto secondPerFrame = std::chrono::milliseconds(1000 / m_FrameRate);

	while (true)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;

		const bool doContinue = input.ProcessInput();
		if (!doContinue)
			break;

		sceneManager.Update(deltaTime);

		renderer.Render();

		// Update FPS display
		const auto& activeScene = sceneManager.GetActiveScene();
		for (const auto& gameObject : activeScene->GetObjects())
		{
			if (const auto fpsCounterComponent = gameObject->GetComponent<FPSCounterComponent>())
			{
				if (const auto fpsTextObject = gameObject->GetComponent<TextComponent>())
				{
					// Format FPS string with one decimal point
					std::stringstream ss;
					ss << "FPS: " << std::fixed << std::setprecision(1) << fpsCounterComponent->GetFPS();
					fpsTextObject->SetText(ss.str());
					break;
				}
			}
		}

		// Sleep to maintain frame rate
		const auto sleepTime = currentTime + std::chrono::milliseconds(secondPerFrame) - std::chrono::high_resolution_clock::now();
		if (sleepTime > std::chrono::milliseconds(0))
		{
			std::this_thread::sleep_for(sleepTime);
		}
	}
}
