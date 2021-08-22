#include "MiniginPCH.h"
#include "Timer.h"

void dae::Timer::Update(float elapsedSec)
{
	m_ElapsedSec = elapsedSec;
}

dae::Timer::Timer()
	: m_ElapsedSec{0.f}
	, m_MsPerUpdate{1.f / 60.f}
{
}
