#pragma once
#include <Component.h>
#include <vector>

namespace dae
{
	class AIComponent;
	class SpriteSheetComponent;
	class Scene;
	class EnemyComponent final : public Component
	{
	public:
		EnemyComponent(EnemyType type, Scene* pScene, bool isControlled = false);

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		virtual void Trigger(Tag triggerTag, GameObject* pGameObject) override;

		EnemyType GetType() const;

		void Reset();

	private:
		bool m_IsControlled;

		int m_CurrentSpriteSheet;

		Scene* m_pScene;

		EnemyType m_Type;

		AIComponent* m_pAIComponent;
		std::vector<SpriteSheetComponent*> m_pSpriteSheetComponents;
		GameObject* m_pTractorBeam;

		MovementDirection m_PreviousDirection;
	};
}