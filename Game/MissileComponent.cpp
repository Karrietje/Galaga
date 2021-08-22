#include "MissileComponent.h"
#include "GameObject.h"
#include "Components.h"
#include "PhysicsManager.h"
#include <iostream>

dae::MissileComponent::MissileComponent(bool enemyMissile)
	: m_EnemyMissile{enemyMissile}
	, m_ShotSpeed{500.f}
{
}

void dae::MissileComponent::Initialize()
{
	TextureComponent* pTextureComponent = new TextureComponent();
	if (m_EnemyMissile)
		pTextureComponent->SetTexture("Sprites/EnemyMissile.png");
	else
		pTextureComponent->SetTexture("Sprites/Missile.png");
	pTextureComponent->SetScale(2.f);
	m_pGameObject->AddComponent(ComponentType::TextureComponent, pTextureComponent);

	TriggerComponent* pTriggerComponent{};
	if (m_EnemyMissile)
		pTriggerComponent = PhysicsManager::GetInstance().CreateTriggerComponent({ 10.f, 5.f }, { 10.f, 22.f }, Tag::EnemyMissile, { Tag::Front });
	else
		pTriggerComponent = PhysicsManager::GetInstance().CreateTriggerComponent({ 10.f, 5.f }, { 10.f, 22.f }, Tag::Missile, { Tag::Back });
	m_pGameObject->AddComponent(ComponentType::TriggerComponent, pTriggerComponent);

	m_pGameObject->SetActive(false);
}

void dae::MissileComponent::Update(float elapsedSec)
{
	glm::vec2 pos{ m_pGameObject->GetTransform()->GetPosition() };
	if (m_EnemyMissile)
		pos.y += (m_ShotSpeed / 2.f) * elapsedSec;
	else
		pos.y -= m_ShotSpeed * elapsedSec;
	m_pGameObject->GetTransform()->SetPosition(pos);
}

void dae::MissileComponent::Render(glm::vec2)
{
}

void dae::MissileComponent::Trigger(Tag triggerTag, GameObject*)
{
	switch (triggerTag)
	{
	case Tag::Back:
	case Tag::Front:
		m_pGameObject->SetActive(false);
		break;
	default:
		break;
	}
}
