#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include "Audio.h"

namespace dae
{
	struct AudioInfo
	{
		bool SoundEffect;
		bool Loop;
		size_t Location;
		int Id;
	};
	
	class AudioService : public Audio
	{
	public:
		AudioService();
		virtual ~AudioService();
		virtual void AddMusic(bool isLoop, int id, const std::string& audioPath) override;
		virtual void AddSoundEffect(int id, const std::string& audioPath) override;
		virtual void PlaySound(int id) override;
		virtual void StopAll() override;

	private:
		void Update();

		std::vector<Mix_Music*> m_pMusic;
		std::vector<Mix_Chunk*> m_pSoundEffects;
		std::vector<AudioInfo> m_Infos;
		std::queue<size_t> m_AudioQueue;
		std::thread m_Thread;
		std::mutex m_Mutex;
		bool m_Stop = false;
	};
}