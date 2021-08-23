#pragma once
#include <Component.h>

namespace dae
{
	class GameObject;
	class Scene;
	class HealthComponent;
	class GalagaManagerComponent : public Component
	{
	public:
		enum class GameMode
		{
			Single, Coop, Versus
		};

		GalagaManagerComponent(GameMode gameMode, Scene* pScene);

		virtual void Initialize() override;
		virtual void PostInitialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void SoftReset();
	
	private:
		int m_MaxLives;

		Scene* m_pScene;

		GameMode m_GameMode;

		HealthComponent* m_pHealthComponent;

		std::vector<GameObject*> m_pSpaceShips;
		std::vector<GameObject*> m_pLives;

		void GoToEndScene();
	};
}