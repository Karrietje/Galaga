#pragma once
#include "Command.h"
#include "SpaceShipComponent.h"
#include "AIComponent.h"

class MoveRightDownCommand final : public Command
{
public:
	MoveRightDownCommand(SpaceShipComponent* pSpaceShip) : m_pSpaceShip{ pSpaceShip } {}
	virtual void Execute() override
	{
		m_pSpaceShip->MoveKeyDown(MovementDirection::Right);
	}

private:
	SpaceShipComponent* m_pSpaceShip;
};

class MoveRightUpCommand final : public Command
{
public:
	MoveRightUpCommand(SpaceShipComponent* pSpaceShip) : m_pSpaceShip{ pSpaceShip } {}
	virtual void Execute() override
	{
		m_pSpaceShip->MoveKeyUp(MovementDirection::Right);
	}

private:
	SpaceShipComponent* m_pSpaceShip;
};

class MoveLeftDownCommand final : public Command
{
public:
	MoveLeftDownCommand(SpaceShipComponent* pSpaceShip) : m_pSpaceShip{ pSpaceShip } {}
	virtual void Execute() override
	{
		m_pSpaceShip->MoveKeyDown(MovementDirection::Left);
	}

private:
	SpaceShipComponent* m_pSpaceShip;
};

class MoveLeftUpCommand final : public Command
{
public:
	MoveLeftUpCommand(SpaceShipComponent* pSpaceShip) : m_pSpaceShip{ pSpaceShip } {}
	virtual void Execute() override
	{
		m_pSpaceShip->MoveKeyUp(MovementDirection::Left);
	}

private:
	SpaceShipComponent* m_pSpaceShip;
};

class ShootCommand final : public Command
{
public:
	ShootCommand(SpaceShipComponent* pSpaceship) : m_pSpaceShip{pSpaceship} {}
	virtual void Execute() override
	{
		if (m_pSpaceShip->GetGameObject()->IsActive())
		{
			m_pSpaceShip->ShootMissile();
			m_pSpaceShip->GetGameObject()->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->Notify(Event::Shot);
		}
	}

private:
	SpaceShipComponent* m_pSpaceShip;
};

class GalagaShootCommand final : public Command
{
public:
	GalagaShootCommand(AIComponent* pGalaga) : m_pGalaga{ pGalaga } {}
	virtual void Execute() override
	{
		m_pGalaga->ShootMissile();
	}

private:
	AIComponent* m_pGalaga;
};

class GalagaTractorBeamCommand final : public Command
{
public:
	GalagaTractorBeamCommand(AIComponent* pGalaga) : m_pGalaga{ pGalaga } {}
	virtual void Execute() override
	{
		m_pGalaga->StartTractorBeamRun();
	}

private:
	AIComponent* m_pGalaga;
};