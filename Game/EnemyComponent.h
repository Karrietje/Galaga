#pragma once
#include <Component.h>
#include <vector>

namespace dae
{
	class AIComponent;
	class SpriteSheetComponent;
	class EnemyComponent final : public Component
	{
	public:
		EnemyComponent(EnemyType type);

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		virtual void Trigger(Tag triggerTag, GameObject* pGameObject) override;

	private:
		int m_CurrentSpriteSheet;

		EnemyType m_Type;

		AIComponent* m_pAIComponent;
		std::vector<SpriteSheetComponent*> m_pSpriteSheetComponents;
		GameObject* m_pTractorBeam;

		MovementDirection m_PreviousDirection;
	};
}