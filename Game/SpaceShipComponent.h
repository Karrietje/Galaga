#pragma once
#include <Component.h>

namespace dae
{
	class GalagaManagerComponent;
	class Scene;
	class SpaceShipComponent : public Component
	{
	public:
		SpaceShipComponent(Scene* pScene, GalagaManagerComponent* pGalagaManagerComponent, int player);

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		virtual void Trigger(Tag triggerTag, GameObject* pGameObject) override;

		void MoveKeyDown(MovementDirection direction);
		void MoveKeyUp(MovementDirection direction);
		void ShootMissile();
		
	private:
		enum class State
		{
			Idle, MovingRight, MovingLeft, Dying
		};

		int m_Player;

		float m_MoveSpeed;
		float m_ShipWidth;
		float m_MaxBoundary;

		State m_State;

		Scene* m_pScene;

		GalagaManagerComponent* m_pGalagaManagerComponent;
	};
}