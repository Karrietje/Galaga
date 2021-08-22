#pragma once
#include "Singleton.h"

namespace dae
{
	class Timer final : public Singleton<Timer>
	{
	public:
		void Update(float elapsedSec);
		
		inline float GetMsPerUpdate() const;
		inline float GetElapsed() const;

	private:
		float m_ElapsedSec;
		float m_MsPerUpdate;

		Timer();
		friend class Singleton<Timer>;
	};

	float Timer::GetMsPerUpdate() const
	{
		return m_MsPerUpdate;
	}

	float Timer::GetElapsed() const
	{
		return m_ElapsedSec;
	}
}