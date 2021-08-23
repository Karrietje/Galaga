#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Timer.h"
#include "AudioLocator.h"
#include "AudioLogger.h"
#include "AudioService.h"
#include "PhysicsManager.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
		throw std::runtime_error(std::string("Sdl_Init Error: ") + SDL_GetError());

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "Core::Initialize( ), error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
		return;
	}

	const int mixerFlags{ MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG };
	if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags)
		std::cerr << "SDL Mixer failed to initialize! Cause of the error: " << Mix_GetError();

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	AudioLocator::RegisterAudio(new AudioLogger{ new AudioService{} });
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
}


void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
	delete AudioLocator::GetAudioSystem();
}

void dae::Minigin::Run()
{
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& physicsManager = PhysicsManager::GetInstance();

	sceneManager.Initialize();
	sceneManager.PostInitialize();

	auto lastTime = high_resolution_clock::now();
	float lag = 0.f;
	bool doContinue = true;
	while (doContinue)
	{
		const auto currentTime = high_resolution_clock::now();
		float deltaTime = duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;
		doContinue = input.ProcessInput();
			
		while (lag >= Timer::GetInstance().GetMsPerUpdate())
		{
			Timer::GetInstance().Update(Timer::GetInstance().GetMsPerUpdate());
			sceneManager.Update(Timer::GetInstance().GetElapsed());
			physicsManager.Update(Timer::GetInstance().GetElapsed());
			sceneManager.LateUpdate();
			lag -= Timer::GetInstance().GetMsPerUpdate();
		}
		renderer.Render();
	}

	Cleanup();
}
