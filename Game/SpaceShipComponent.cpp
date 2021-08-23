#include "SpaceShipComponent.h"
#include "Components.h"
#include "GameObject.h"
#include "GalagaCommands.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include "MissileManager.h"
#include "GalagaManagerComponent.h"
#include "Audio.h"
#include "AudioLocator.h"
#include <SDL.h>
#include <string>

dae::SpaceShipComponent::SpaceShipComponent(Scene* pScene, GalagaManagerComponent* pGalagaManagerComponent, int player)
	: m_Player{player}
	, m_MoveSpeed{500.f}
	, m_ShipWidth{32.f}
	, m_MaxBoundary{640.f}
	, m_State{State::Idle}
	, m_pScene{pScene}
	, m_pGalagaManagerComponent{pGalagaManagerComponent}
{
}

void dae::SpaceShipComponent::Initialize()
{
	auto spriteComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo;
	spriteInfo.rows = 1;
	spriteInfo.colums = 1;

	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::Up] = std::make_pair(0, 1);

	std::string spriteName{ "Sprites/Spaceship" + std::to_string(m_Player) + ".png" };
	spriteComponent->SetSprite(spriteName, spriteInfo);
	spriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::Up);
	spriteComponent->SetScale(2.f);

	m_pGameObject->AddComponent(ComponentType::SpriteSheetComponent, spriteComponent);

	TriggerComponent* pTriggerComponent = PhysicsManager::GetInstance().CreateTriggerComponent({ 0.f, 0.f }, { 32.f, 32.f }, Tag::Spaceship, { Tag::Enemy, Tag::EnemyMissile, Tag::TractorBeam });
	m_pGameObject->AddComponent(ComponentType::TriggerComponent, pTriggerComponent);

	MissileManager::GetInstance().SubscribeGameObject(m_pScene, m_pGameObject);

	MoveRightDownCommand* pMoveRightDown = new MoveRightDownCommand(this);
	InputManager::GetInstance().AddCommand(ControllerInput{ (m_Player == 0 ? SDLK_d : SDLK_RIGHT), VK_PAD_DPAD_RIGHT, InputType::KeyDown, m_Player }, pMoveRightDown);

	MoveRightUpCommand* pMoveRightUp = new MoveRightUpCommand(this);
	InputManager::GetInstance().AddCommand(ControllerInput{ (m_Player == 0 ? SDLK_d : SDLK_RIGHT), VK_PAD_DPAD_RIGHT, InputType::KeyUp, m_Player }, pMoveRightUp);

	MoveLeftDownCommand* pMoveLeftDown = new MoveLeftDownCommand(this);
	InputManager::GetInstance().AddCommand(ControllerInput{ (m_Player == 0 ? SDLK_a : SDLK_LEFT), VK_PAD_DPAD_LEFT, InputType::KeyDown, m_Player }, pMoveLeftDown);

	MoveLeftUpCommand* pMoveLeftUp = new MoveLeftUpCommand(this);
	InputManager::GetInstance().AddCommand(ControllerInput{ (m_Player == 0 ? SDLK_a : SDLK_LEFT), VK_PAD_DPAD_LEFT, InputType::KeyUp, m_Player }, pMoveLeftUp);

	ShootCommand* pShoot = new ShootCommand(this);
	InputManager::GetInstance().AddCommand(ControllerInput{ (m_Player == 0 ? SDLK_SPACE : SDLK_UP), VK_PAD_A, InputType::KeyDown, m_Player }, pShoot);

	SubjectComponent* subjectComp = new SubjectComponent();
	m_pGameObject->AddComponent(ComponentType::SubjectComponent, subjectComp);
}

void dae::SpaceShipComponent::Update(float elapsedSec)
{
	float newX{};
	glm::vec2 pos{ m_pGameObject->GetTransform()->GetPosition() };
	switch (m_State)
	{
	case dae::SpaceShipComponent::State::Idle:
		break;
	case dae::SpaceShipComponent::State::MovingRight:
		newX = pos.x + (m_MoveSpeed * elapsedSec);
		if (newX < (m_MaxBoundary - m_ShipWidth))
			pos.x = newX;
		break;
	case dae::SpaceShipComponent::State::MovingLeft:
		newX = pos.x - (m_MoveSpeed * elapsedSec);
		if (newX > 0)
			pos.x = newX;
		break;
	case dae::SpaceShipComponent::State::Dying:
		break;
	default:
		break;
	}
	m_pGameObject->GetTransform()->SetPosition(pos);
}

void dae::SpaceShipComponent::Render(glm::vec2)
{
}

void dae::SpaceShipComponent::Trigger(Tag triggerTag, GameObject*)
{
	AudioLocator::GetAudioSystem()->Play(7);
	switch (triggerTag)
	{
	case Tag::EnemyMissile:
		m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->Notify(Event::Kill);
		m_pGalagaManagerComponent->SoftReset();
		break;
	case Tag::Enemy:
		m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->Notify(Event::Kill);
		m_pGalagaManagerComponent->SoftReset();
		break;
	case Tag::TractorBeam:
		m_pGameObject->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->Notify(Event::Kill);
		m_pGalagaManagerComponent->SoftReset();
		break;
	default:
		break;
	}
}

void dae::SpaceShipComponent::MoveKeyDown(MovementDirection direction)
{
	switch (direction)
	{
	case MovementDirection::Right:
		m_State = State::MovingRight;
		break;
	case MovementDirection::Left:
		m_State = State::MovingLeft;
		break;
	default:
		break;
	}
}

void dae::SpaceShipComponent::MoveKeyUp(MovementDirection direction)
{
	switch (direction)
	{

	case MovementDirection::Right:
		if (m_State == State::MovingRight)
			m_State = State::Idle;
		break;
	case MovementDirection::Left:
		if (m_State == State::MovingLeft)
			m_State = State::Idle;
		break;
	default:
		break;
	}
}

void dae::SpaceShipComponent::ShootMissile()
{
	if (MissileManager::GetInstance().ShootMissile(m_pGameObject))
		AudioLocator::GetAudioSystem()->Play(2);
}
