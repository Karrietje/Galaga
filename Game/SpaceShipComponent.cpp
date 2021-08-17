#include "SpaceShipComponent.h"
#include "Components.h"
#include "GameObject.h"
#include "GalagaCommands.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include "MissileManager.h"
#include <SDL.h>

dae::SpaceShipComponent::SpaceShipComponent()
	: m_MoveSpeed{500.f}
	, m_ShipWidth{32.f}
	, m_MaxBoundary{640.f}
	, m_State{State::Idle}
{
}

void dae::SpaceShipComponent::Initialize()
{
	auto spriteComponent = new SpriteSheetComponent();
	SpriteSheetComponent::SpriteInfo spriteInfo;
	spriteInfo.rows = 1;
	spriteInfo.colums = 1;

	spriteInfo.SheetInfo[SpriteSheetComponent::SpriteState::Up] = std::make_pair(0, 1);

	std::string spriteName{ "Sprites/Spaceship.png" };
	spriteComponent->SetSprite(spriteName, spriteInfo);
	spriteComponent->SetSpriteState(SpriteSheetComponent::SpriteState::Up);
	spriteComponent->SetScale(2.f);

	m_pGameObject->AddComponent(ComponentType::SpriteSheetComponent, spriteComponent);

	TriggerComponent* pTriggerComponent = PhysicsManager::GetInstance().CreateTriggerComponent({ 0.f, 0.f }, { 32.f, 32.f }, Tag::Spaceship, { Tag::Enemy });
	m_pGameObject->AddComponent(ComponentType::TriggerComponent, pTriggerComponent);

	m_pGameObject->GetTransform()->SetPosition({ 300, 400 });

	MissileManager::GetInstance().SubscribeSpaceship(this);

	MoveRightDownCommand* pMoveRightDown = new MoveRightDownCommand(this);
	InputManager::GetInstance().AddCommand(ControllerInput{ SDLK_d, VK_PAD_DPAD_RIGHT, InputType::KeyDown, 0 }, pMoveRightDown);

	MoveRightUpCommand* pMoveRightUp = new MoveRightUpCommand(this);
	InputManager::GetInstance().AddCommand(ControllerInput{ SDLK_d, VK_PAD_DPAD_RIGHT, InputType::KeyUp, 0 }, pMoveRightUp);

	MoveLeftDownCommand* pMoveLeftDown = new MoveLeftDownCommand(this);
	InputManager::GetInstance().AddCommand(ControllerInput{ SDLK_a, VK_PAD_DPAD_LEFT, InputType::KeyDown, 0 }, pMoveLeftDown);

	MoveLeftUpCommand* pMoveLeftUp = new MoveLeftUpCommand(this);
	InputManager::GetInstance().AddCommand(ControllerInput{ SDLK_a, VK_PAD_DPAD_LEFT, InputType::KeyUp, 0 }, pMoveLeftUp);

	ShootCommand* pShoot = new ShootCommand(this);
	InputManager::GetInstance().AddCommand(ControllerInput{ SDLK_SPACE, VK_PAD_A, InputType::KeyDown, 0 }, pShoot);

	m_Initialized = true;
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
	MissileManager::GetInstance().ShootMissile(this);
}
