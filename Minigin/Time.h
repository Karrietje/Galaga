#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void Update(float elapsedSec);
		
		inline float GetMsPerUpdate() const;
		inline float GetElapsed() const;

	private:
		float m_ElapsedSec;
		float m_MsPerUpdate;

		Time();
		friend class Singleton<Time>;
	};

	float Time::GetMsPerUpdate() const
	{
		return m_MsPerUpdate;
	}

	float Time::GetElapsed() const
	{
		return m_ElapsedSec;
	}
}