#include "ZakoComponent.h"
#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "GalagaComponents.h"

void dae::ZakoComponent::Initialize()
{
	SpriteSheetComponent* pSpriteSheetComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo{};
	spriteInfo.rows = 1;
	spriteInfo.colums = 2;

	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::Up] = std::make_pair(0, 2);

	std::string spriteName{ "Sprites/Zako.png" };
	pSpriteSheetComponent->SetSprite(spriteName, spriteInfo);
	pSpriteSheetComponent->SetSpriteState(SpriteSheetComponent::SpriteState::Up);
	pSpriteSheetComponent->SetScale(2.f);
	pSpriteSheetComponent->SetFrameTime(0.5f);

	m_pGameObject->AddComponent(ComponentType::SpriteSheetComponent, pSpriteSheetComponent);

	TriggerComponent* pTriggerComponent = PhysicsManager::GetInstance().CreateTriggerComponent({ 0.f, 0.f }, { 32.f, 32.f }, Tag::Enemy, {  });
	m_pGameObject->AddComponent(ComponentType::TriggerComponent, pTriggerComponent);

	AIComponent* pAIComponent = new AIComponent();
	m_pGameObject->AddComponent(ComponentType::AIComponent, pAIComponent);

	m_Initialized = true;
}

void dae::ZakoComponent::Update(float)
{
}

void dae::ZakoComponent::Render(glm::vec2)
{
}
