#pragma once

namespace dae
{
	class Audio
	{
	public:
		virtual ~Audio() = default;
		virtual void AddMusic(bool isLoop, int id, const std::string& audioPath) = 0;
		virtual void AddSoundEffect(int id, const std::string& audioPath) = 0;
		virtual void Play(int id) = 0;
		virtual void StopAll() = 0;
	};
}