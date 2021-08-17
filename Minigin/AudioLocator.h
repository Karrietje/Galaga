#pragma once

namespace dae
{
	class Audio;
	class DefaultAudio;
	
	class AudioLocator
	{
	public:
		static Audio* GetAudioSystem();
		static void RegisterAudio(Audio* audio);

	private:
		AudioLocator() = default;

		static DefaultAudio m_DefaultAudio;
		static Audio* m_Audio;
	};
}