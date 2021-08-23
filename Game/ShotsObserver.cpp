#include "ShotsObserver.h"
#include <iostream>
#include <string>

int dae::ShotsObserver::m_ShotsFired{ 0 };
int dae::ShotsObserver::m_ShotsHit{ 0 };

void dae::ShotsObserver::Notify(Event event)
{
	switch (event)
	{
	case Event::Shot:
		m_ShotsFired++;
		break;
	case Event::Hit:
		m_ShotsHit++;
		break;
	default:
		break;
	}
}

int dae::ShotsObserver::GetShotsFired()
{
    return m_ShotsFired;
}

int dae::ShotsObserver::GetShotsHit()
{
    return m_ShotsHit;
}
