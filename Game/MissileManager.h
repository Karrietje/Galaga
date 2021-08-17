#pragma once
#include "Singleton.h"
#include <vector>
#include <map>

namespace dae
{
	class Scene;
	class MissileComponent;
	class SpaceShipComponent;
	class MissileManager final : public Singleton<MissileManager>
	{
	public:
		inline void SetScene(Scene* pScene);

		void SubscribeSpaceship(SpaceShipComponent* pSpaceShip);
		void ShootMissile(SpaceShipComponent* pSpaceShip);

	private:
		friend class Singleton<MissileManager>;
		MissileManager() = default;
		
		Scene* m_pScene;

		std::map<SpaceShipComponent*, std::vector<MissileComponent*>> m_pMissiles;
	};

	inline void dae::MissileManager::SetScene(Scene* pScene)
	{
		m_pScene = pScene;
	}
}