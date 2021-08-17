#include "MiniginPCH.h"
#include "AudioLogger.h"

dae::AudioLogger::AudioLogger(Audio* audio, bool isMuted)
	: m_pAudioService{audio}
	, m_IsMuted{isMuted}
{
}

dae::AudioLogger::~AudioLogger()
{
	delete m_pAudioService;
}

void dae::AudioLogger::AddMusic(bool isLoop, int id, const std::string& audioPath)
{
	if (!m_IsMuted)
		m_pAudioService->AddMusic(isLoop, id, audioPath);
}

void dae::AudioLogger::AddSoundEffect(int id, const std::string& audioPath)
{
	if (!m_IsMuted)
		m_pAudioService->AddSoundEffect(id, audioPath);
}

void dae::AudioLogger::PlaySound(int id)
{
	if (!m_IsMuted)
		m_pAudioService->PlaySound(id);
}

void dae::AudioLogger::StopAll()
{
	if (!m_IsMuted)
		m_pAudioService->StopAll();
}
