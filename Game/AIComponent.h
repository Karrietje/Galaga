#pragma once
#include <Component.h>

namespace dae
{
	class Scene;
	class AIComponent final : public Component
	{
	public:
		enum class AIState
		{
			Idle, Bombing, Moving, TractorBeam, Returning
		};

		AIComponent(Scene* pScene, EnemyType type, bool isControlled);

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		virtual void Trigger(Tag triggerTag, GameObject* pGameObject) override;

		static void UpdateOriginalPos(float elapsedSec);

		void ChangeControl(bool control);

		AIState GetState() const;
		MovementDirection GetDirection() const;

		void Reset();

		void ShootMissile();
		void StartTractorBeamRun();

	private:
		bool m_IsControlled;

		float m_MoveTimer;
		float m_MissileTimer;
		const float m_MissileTime;
		const float m_BombingTime;
		const float m_ChangeDirectionTime;
		const float m_TractorBeamTime;
		const float m_BombingSpeed;
		const float m_DiagonalBombingSpeed;

		static float m_StaticOriginalPosX;
		static const float m_IdleSpeed;
		static const float m_SpriteWidth;

		glm::vec2 m_Boundaries;
		glm::vec2 m_OriginalPosition;
		const glm::vec2 m_ScreenBoundaries;

		Scene* m_pScene;

		EnemyType m_Type;
		AIState m_AIState;
		MovementDirection m_Direction;
		static MovementDirection m_OriginalDirection;

		void MissileHandling(float elapsedSec);

		glm::vec2 Idle(float elapsedSec);

		glm::vec2 ZakoBombing(float elapsedSec);
		glm::vec2 GoeiBombing(float elapsedSec);

		glm::vec2 BossTractorBeam(float elapsedSec);

		glm::vec2 Returning(float elapsedSec);
	};
}