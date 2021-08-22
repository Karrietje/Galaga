#include "GalagaManagerComponent.h"
#include "GameObject.h"
#include "GalagaComponents.h"
#include "Scene.h"
#include "MissileManager.h"
#include "Components.h"
#include "PhysicsManager.h"

dae::GalagaManagerComponent::GalagaManagerComponent(Scene* pGalagaScene)
	: m_pGalagaScene(pGalagaScene)
{
}

void dae::GalagaManagerComponent::Initialize()
{
	MissileManager::GetInstance().SetScene(m_pGalagaScene);

	GameObject* pSpaceship = new GameObject();

	SpaceShipComponent* pSpaceshipComponent = new SpaceShipComponent();
	pSpaceship->AddComponent(ComponentType::SpaceShipComponent, pSpaceshipComponent);

	m_pGalagaScene->Add(pSpaceship, 3);

	GameObject* pBack = new GameObject();

	TriggerComponent* pBackTrigger = PhysicsManager::GetInstance().CreateTriggerComponent({ 0, 0 }, { 640, 1 }, Tag::Back, {});
	pBack->AddComponent(ComponentType::TriggerComponent, pBackTrigger);

	m_pGalagaScene->Add(pBack, 0);

	GameObject* pFront = new GameObject();

	TriggerComponent* pFrontTrigger = PhysicsManager::GetInstance().CreateTriggerComponent({ 0, 479 }, { 640, 1 }, Tag::Front, {});
	pFront->AddComponent(ComponentType::TriggerComponent, pFrontTrigger);

	m_pGalagaScene->Add(pFront, 0);

	GameObject* pTractorBeamFront = new GameObject();

	TriggerComponent* pTractorBeamFrontTrigger = PhysicsManager::GetInstance().CreateTriggerComponent({ 0, 320 }, { 640, 1 }, Tag::TractorBeamFront, {});
	pTractorBeamFront->AddComponent(ComponentType::TriggerComponent, pTractorBeamFrontTrigger);

	m_pGalagaScene->Add(pTractorBeamFront, 0);

	for (int i{}; i < 4; i++)
	{
		GameObject* pZako = new GameObject();

		EnemyComponent* pEnemyComponent = new EnemyComponent(EnemyType::Boss);
		pZako->AddComponent(ComponentType::ZakoComponent, pEnemyComponent);

		pZako->GetTransform()->SetPosition({ 196 + (i * 32), 32 });
		m_pGalagaScene->Add(pZako, 4);
	}

	for (int i{}; i < 10; i++)
	{
		GameObject* pGoei = new GameObject();

		EnemyComponent* pEnemyComponent = new EnemyComponent(EnemyType::Goei);
		pGoei->AddComponent(ComponentType::ZakoComponent, pEnemyComponent);

		pGoei->GetTransform()->SetPosition({ 100 + (i * 32), 64 });
		m_pGalagaScene->Add(pGoei, 4);
	}

	for (int i{}; i < 10; i++)
	{
		GameObject* pGoei = new GameObject();

		EnemyComponent* pEnemyComponent = new EnemyComponent(EnemyType::Zako);
		pGoei->AddComponent(ComponentType::ZakoComponent, pEnemyComponent);

		pGoei->GetTransform()->SetPosition({ 100 + (i * 32), 96 });
		m_pGalagaScene->Add(pGoei, 4);
	}
}

void dae::GalagaManagerComponent::Update(float)
{
}

void dae::GalagaManagerComponent::Render(glm::vec2)
{
}
