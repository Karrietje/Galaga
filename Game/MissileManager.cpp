#include "MissileManager.h"
#include "GameObject.h"
#include "Components.h"
#include "GalagaComponents.h"
#include "Scene.h"

void dae::MissileManager::SubscribeSpaceship(SpaceShipComponent* pSpaceShip)
{
	if (m_pMissiles.find(pSpaceShip) != m_pMissiles.end())
		return;

	m_pMissiles.insert(std::make_pair(pSpaceShip, std::vector<MissileComponent*>()));

	for (int i{}; i < 2; i++)
	{
		GameObject* pMissile = new GameObject();

		MissileComponent* pMissileComponent = new MissileComponent();
		pMissile->AddComponent(ComponentType::MissileComponent, pMissileComponent);

		m_pMissiles.at(pSpaceShip).push_back(pMissileComponent);

		m_pScene->Add(pMissile, 3);
	}
}

void dae::MissileManager::ShootMissile(SpaceShipComponent* pSpaceShip)
{
	for (MissileComponent* pMissile : m_pMissiles.at(pSpaceShip))
	{
		GameObject* pMissileObject{ pMissile->GetGameObject() };
		if (!pMissileObject->IsActive())
		{
			pMissileObject->GetTransform()->SetPosition(pSpaceShip->GetGameObject()->GetTransform()->GetPosition());
			pMissileObject->SetActive(true);
			return;
		}
	}
}
