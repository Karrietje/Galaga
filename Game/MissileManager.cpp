#include "MissileManager.h"
#include "GameObject.h"
#include "Components.h"
#include "GalagaComponents.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::MissileManager::SubscribeGameObject(Scene* pScene, GameObject* pGameObject, bool isEnemy)
{
	if (m_pMissiles.find(pGameObject) != m_pMissiles.end())
		return;

	m_pMissiles.insert(std::make_pair(pGameObject, std::vector<MissileComponent*>()));

	for (int i{}; i < 2; i++)
	{
		GameObject* pMissile = new GameObject();

		MissileComponent* pMissileComponent = new MissileComponent(isEnemy);
		pMissile->AddComponent(ComponentType::MissileComponent, pMissileComponent);

		m_pMissiles.at(pGameObject).push_back(pMissileComponent);

		pScene->Add(pMissile, 3);
	}
}

bool dae::MissileManager::ShootMissile(GameObject* pGameObject)
{
	for (MissileComponent* pMissile : m_pMissiles.at(pGameObject))
	{
		GameObject* pMissileObject{ pMissile->GetGameObject() };
		if (!pMissileObject->IsActive())
		{
			pMissileObject->GetTransform()->SetPosition(pGameObject->GetTransform()->GetPosition());
			pMissileObject->SetActive(true);
			return true;
		}
	}
	return false;
}

void dae::MissileManager::Reset()
{
	for (std::pair<GameObject*, std::vector<MissileComponent*>> missiles : m_pMissiles)
	{
		for (MissileComponent* pMissile : missiles.second)
		{
			pMissile->GetGameObject()->SetActive(false);
		}
	}
}
