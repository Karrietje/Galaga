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

	GameObject* pZako = new GameObject();

	ZakoComponent* pZakoComponent = new ZakoComponent();
	pZako->AddComponent(ComponentType::ZakoComponent, pZakoComponent);

	pZako->GetTransform()->SetPosition({ 100, 100 });

	m_pGalagaScene->Add(pZako, 4);

	m_Initialized = true;
}

void dae::GalagaManagerComponent::Update(float)
{
}

void dae::GalagaManagerComponent::Render(glm::vec2)
{
}
