#include "MissileComponent.h"
#include "GameObject.h"
#include "Components.h"
#include "PhysicsManager.h"
#include <iostream>

dae::MissileComponent::MissileComponent()
	: m_IsHit{false}
	, m_ShotSpeed{500.f}
{
}

void dae::MissileComponent::Initialize()
{
	TextureComponent* pTextureComponent = new TextureComponent();
	pTextureComponent->SetTexture("Sprites/Missile.png");
	pTextureComponent->SetScale(2.f);
	m_pGameObject->AddComponent(ComponentType::TextureComponent, pTextureComponent);

	TriggerComponent* pTriggerComponent = PhysicsManager::GetInstance().CreateTriggerComponent({ 10.f, 5.f }, { 10.f, 22.f }, Tag::Missile, { Tag::Enemy, Tag::Back });
	m_pGameObject->AddComponent(ComponentType::TriggerComponent, pTriggerComponent);

	m_pGameObject->SetActive(false);

	m_Initialized = true;
}

void dae::MissileComponent::Update(float elapsedSec)
{
	if (m_IsHit)
	{
		m_IsHit = false;
		m_pGameObject->SetActive(false);
	}

	glm::vec2 pos{ m_pGameObject->GetTransform()->GetPosition() };
	pos.y -= m_ShotSpeed * elapsedSec;
	m_pGameObject->GetTransform()->SetPosition(pos);
}

void dae::MissileComponent::Render(glm::vec2)
{
}

void dae::MissileComponent::Trigger(Tag triggerTag, GameObject* pGameObject)
{
	switch (triggerTag)
	{
	case Tag::Enemy:
		m_IsHit = true;
		pGameObject->SetActive(false);
		break;
	case Tag::Back:
		m_IsHit = true;
		break;
	default:
		break;
	}
}
