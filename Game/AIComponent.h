#pragma once
#include <Component.h>

namespace dae
{
	class AIComponent final : public Component
	{
	public:
		AIComponent();

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

	private:
		enum class State
		{
			Idle, Bombing
		};

		float m_IdleSpeed;
		float m_BombingSpeed;

		glm::vec2 m_Boundaries;

		State m_State;
		MovementDirection m_Direction;
	};
}