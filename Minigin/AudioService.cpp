#include "MiniginPCH.h"
#include "AudioService.h"
#include "ResourceManager.h"

dae::AudioService::AudioService()
	: m_Thread{&dae::AudioService::Update, this}
{
}

dae::AudioService::~AudioService()
{
	for (Mix_Music* pMusic : m_pMusic)
		Mix_FreeMusic(pMusic);

	for (Mix_Chunk* pSoundEffect : m_pSoundEffects)
		Mix_FreeChunk(pSoundEffect);

	m_Stop = true;
	m_Thread.join();
}

void dae::AudioService::AddMusic(bool isLoop, int id, const std::string& audioPath)
{
	m_Infos.push_back(AudioInfo{false, isLoop, m_pMusic.size(), id });
	m_pMusic.push_back(Mix_LoadMUS((ResourceManager::GetInstance().GetDataPath() + audioPath).c_str()));
}

void dae::AudioService::AddSoundEffect(int id, const std::string& audioPath)
{
	m_Infos.push_back(AudioInfo{true, false, m_pSoundEffects.size(), id });
	m_pSoundEffects.push_back(Mix_LoadWAV((ResourceManager::GetInstance().GetDataPath() + audioPath).c_str()));
}

void dae::AudioService::PlaySound(int id)
{
	for(size_t i{}; i < m_Infos.size(); i++)
	{
		if (m_Infos[i].Id == id)
		{
			m_AudioQueue.push(i);
		}
	}
}

void dae::AudioService::StopAll()
{
	Mix_HaltChannel(-1);
}

void dae::AudioService::Update()
{
	while(!m_Stop)
	{
		std::unique_lock<std::mutex> mutex{ m_Mutex };

		if (!m_AudioQueue.empty())
		{
			AudioInfo audio = m_Infos[m_AudioQueue.back()];
			m_AudioQueue.pop();
			if (audio.SoundEffect)
				Mix_PlayChannel(-1, m_pSoundEffects[audio.Location], 0);
			else
				Mix_PlayMusic(m_pMusic[audio.Location], audio.Loop);
		}

		mutex.unlock();
	}
}
