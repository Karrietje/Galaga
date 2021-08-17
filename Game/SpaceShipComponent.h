#pragma once
#include <Component.h>

namespace dae
{
	class SpaceShipComponent : public Component
	{
	public:
		SpaceShipComponent();

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void MoveKeyDown(MovementDirection direction);
		void MoveKeyUp(MovementDirection direction);
		void ShootMissile();
		
	private:
		enum class State
		{
			Idle, MovingRight, MovingLeft, Dying
		};

		float m_MoveSpeed;
		float m_ShipWidth;
		float m_MaxBoundary;

		State m_State;
	};
}