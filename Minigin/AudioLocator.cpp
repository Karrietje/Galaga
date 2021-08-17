#include "MiniginPCH.h"
#include "AudioLocator.h"
#include "Audio.h"
#include "DefaultAudio.h"

dae::DefaultAudio dae::AudioLocator::m_DefaultAudio{};
dae::Audio* dae::AudioLocator::m_Audio = &m_DefaultAudio;


dae::Audio* dae::AudioLocator::GetAudioSystem()
{
	return m_Audio;
}

void dae::AudioLocator::RegisterAudio(Audio* audio)
{
	m_Audio = audio;
}
