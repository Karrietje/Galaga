#pragma once
#include "Audio.h"

namespace dae
{
	class AudioLogger : public Audio
	{
	public:
		AudioLogger(Audio* audio, bool isMuted = false);
		virtual ~AudioLogger();
		virtual void AddMusic(bool isLoop, int id, const std::string& audioPath) override;
		virtual void AddSoundEffect(int id, const std::string& audioPath) override;
		virtual void PlaySound(int id) override;
		virtual void StopAll() override;

	private:
		Audio* m_pAudioService;
		bool m_IsMuted;
	};
}