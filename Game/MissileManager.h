#pragma once
#include "Singleton.h"
#include <vector>
#include <map>

namespace dae
{
	class MissileComponent;
	class GameObject;
	class Scene;
	class MissileManager final : public Singleton<MissileManager>
	{
	public:
		void SubscribeGameObject(Scene* pScene, GameObject* pGameObject, bool isEnemy = false);
		bool ShootMissile(GameObject* pGameObject);

		void Reset();
	private:
		friend class Singleton<MissileManager>;
		MissileManager() = default;

		std::map<GameObject*, std::vector<MissileComponent*>> m_pMissiles;
	};
}