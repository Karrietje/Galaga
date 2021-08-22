#include "EnemyComponent.h"
#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "GalagaComponents.h"
#include "SceneManager.h"
#include "Scene.h"

dae::EnemyComponent::EnemyComponent(EnemyType type)
	: m_CurrentSpriteSheet{0}
	, m_Type{type}
{
}

void dae::EnemyComponent::Initialize()
{
	SpriteSheetComponent* pSpriteSheetComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo{};
	spriteInfo.rows = 8;
	spriteInfo.colums = 3;

	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::Up] = std::make_pair(0, 2);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::UpRight] = std::make_pair(1, 3);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::Right] = std::make_pair(2, 3);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::DownRight] = std::make_pair(3, 3);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::Down] = std::make_pair(4, 2);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::DownLeft] = std::make_pair(5, 3);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::Left] = std::make_pair(6, 3);
	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::UpLeft] = std::make_pair(7, 3);

	std::string spriteName{};
	switch (m_Type)
	{
	case EnemyType::Zako:
		spriteName = "Sprites/Zako.png";
		break;
	case EnemyType::Goei:
		spriteName = "Sprites/Goei.png";
		break;
	case EnemyType::Boss:
		spriteName = "Sprites/BossGreen.png";
		break;
	default:
		break;
	}

	pSpriteSheetComponent->SetSprite(spriteName, spriteInfo);
	pSpriteSheetComponent->SetSpriteState(SpriteSheetComponent::SpriteState::Up);
	m_PreviousDirection = MovementDirection::Up;
	pSpriteSheetComponent->SetScale(2.f);
	pSpriteSheetComponent->SetFrameTime(0.5f);
	m_pSpriteSheetComponents.push_back(pSpriteSheetComponent);
	m_pGameObject->AddComponent(ComponentType::SpriteSheetComponent, pSpriteSheetComponent);

	if (m_Type == EnemyType::Boss)
	{
		pSpriteSheetComponent = new SpriteSheetComponent();
		spriteName = "Sprites/BossPurple.png";
		pSpriteSheetComponent->SetSprite(spriteName, spriteInfo);
		pSpriteSheetComponent->SetSpriteState(SpriteSheetComponent::SpriteState::Up);
		m_PreviousDirection = MovementDirection::Up;
		pSpriteSheetComponent->SetScale(2.f);
		pSpriteSheetComponent->SetFrameTime(0.5f);
		pSpriteSheetComponent->SetActive(false);
		m_pSpriteSheetComponents.push_back(pSpriteSheetComponent);
		m_pGameObject->AddComponent(ComponentType::SpriteSheetComponent, pSpriteSheetComponent);

		m_pTractorBeam = new GameObject();

		SpriteSheetComponent* pTractorBeamSpriteSheet = new SpriteSheetComponent();
		spriteInfo.rows = 1;
		spriteInfo.colums = 3;
		spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::Up] = std::make_pair(0, 3);
		pTractorBeamSpriteSheet->SetSprite("Sprites/TractorBeam.png", spriteInfo);
		pTractorBeamSpriteSheet->SetSpriteState(SpriteSheetComponent::SpriteState::Up);
		pTractorBeamSpriteSheet->SetScale(2.f);
		pTractorBeamSpriteSheet->SetFrameTime(0.1f);
		m_pTractorBeam->AddComponent(ComponentType::SpriteSheetComponent, pTractorBeamSpriteSheet);

		TriggerComponent* pTractorBeamTriggerComponent = PhysicsManager::GetInstance().CreateTriggerComponent({ 0, 0 }, { 96, 160 }, Tag::TractorBeam, {});
		m_pTractorBeam->AddComponent(ComponentType::TriggerComponent, pTractorBeamTriggerComponent);

		SceneManager::GetInstance().GetCurrentScene()->Add(m_pTractorBeam, 4);
		m_pGameObject->AddChild(m_pTractorBeam);
		m_pTractorBeam->GetTransform()->SetPosition({ -32.f, 32.f });
		m_pTractorBeam->SetActive(false);
	}


	TriggerComponent* pTriggerComponent = PhysicsManager::GetInstance().CreateTriggerComponent({ 0.f, 0.f }, { 32.f, 32.f }, Tag::Enemy, { Tag::Spaceship, Tag::Front, Tag::TractorBeamFront, Tag::Missile });
	m_pGameObject->AddComponent(ComponentType::TriggerComponent, pTriggerComponent);

	m_pAIComponent = new AIComponent(m_Type);
	m_pGameObject->AddComponent(ComponentType::AIComponent, m_pAIComponent);
}

void dae::EnemyComponent::Update(float)
{
	if (m_Type == EnemyType::Boss)
	{
		if (m_pAIComponent->GetState() == AIComponent::AIState::TractorBeam)
			m_pTractorBeam->SetActive(true);
		else
			m_pTractorBeam->SetActive(false);
	}
	MovementDirection currentDirection{m_pAIComponent->GetDirection()};
	if (m_PreviousDirection != currentDirection)
	{
		SpriteSheetComponent::SpriteState state{};
		switch (currentDirection)
		{
		case MovementDirection::Up:
			state = SpriteSheetComponent::SpriteState::Up;
			break;
		case MovementDirection::UpRight:
			state = SpriteSheetComponent::SpriteState::UpRight;
			break;
		case MovementDirection::Right:
			state = SpriteSheetComponent::SpriteState::Right;
			break;
		case MovementDirection::DownRight:
			state = SpriteSheetComponent::SpriteState::DownRight;
			break;
		case MovementDirection::Down:
			state = SpriteSheetComponent::SpriteState::Down;
			break;
		case MovementDirection::DownLeft:
			state = SpriteSheetComponent::SpriteState::DownLeft;
			break;
		case MovementDirection::Left:
			state = SpriteSheetComponent::SpriteState::Left;
			break;
		case MovementDirection::UpLeft:
			state = SpriteSheetComponent::SpriteState::UpLeft;
			break;
		default:
			break;
		}
		m_PreviousDirection = currentDirection;
		m_pSpriteSheetComponents[m_CurrentSpriteSheet]->SetSpriteState(state);
	}
}

void dae::EnemyComponent::Render(glm::vec2)
{
}

void dae::EnemyComponent::Trigger(Tag triggerTag, GameObject* pGameObject)
{
	switch (triggerTag)
	{
	case Tag::Spaceship:
		break;
	case Tag::Missile:
		pGameObject->SetActive(false);
		switch (m_Type)
		{
		case EnemyType::Zako:
			m_pGameObject->SetActive(false);
			break;
		case EnemyType::Goei:
			m_pGameObject->SetActive(false);
			break;
		case EnemyType::Boss:
			if (m_CurrentSpriteSheet == 0)
			{
				m_pSpriteSheetComponents[m_CurrentSpriteSheet]->SetActive(false);
				m_CurrentSpriteSheet += 1;
				m_pSpriteSheetComponents[m_CurrentSpriteSheet]->SetActive(true);
			}
			else if (m_CurrentSpriteSheet == 1)
			{
				m_pGameObject->SetActive(false);
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
