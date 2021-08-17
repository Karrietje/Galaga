#include "MiniginPCH.h"
#include "Time.h"

void dae::Time::Update(float elapsedSec)
{
	m_ElapsedSec = elapsedSec;
}

dae::Time::Time()
	: m_ElapsedSec{0.f}
	, m_MsPerUpdate{1.f / 60.f}
{
}
