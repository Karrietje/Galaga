#pragma once
#include "Singleton.h"
#include <vector>
#include <map>

namespace dae
{
	class Scene;
	class MissileComponent;
	class GameObject;
	class MissileManager final : public Singleton<MissileManager>
	{
	public:
		inline void SetScene(Scene* pScene);

		void SubscribeGameObject(GameObject* pGameObject, bool isEnemy = false);
		void ShootMissile(GameObject* pGameObject);

	private:
		friend class Singleton<MissileManager>;
		MissileManager() = default;
		
		Scene* m_pScene;

		std::map<GameObject*, std::vector<MissileComponent*>> m_pMissiles;
	};

	inline void dae::MissileManager::SetScene(Scene* pScene)
	{
		m_pScene = pScene;
	}
}