#include "AIComponent.h"
#include "GameObject.h"
#include "Components.h"

dae::AIComponent::AIComponent()
	: m_IdleSpeed{32.f}
	, m_BombingSpeed{64.f}
	, m_Boundaries{}
	, m_State{State::Idle}
	, m_Direction{MovementDirection::Right}
{
}

void dae::AIComponent::Initialize()
{
	m_Boundaries.x = m_pGameObject->GetTransform()->GetPosition().x;
	m_Boundaries.y = m_Boundaries.x + 160.f;
}

void dae::AIComponent::Update(float elapsedSec)
{
	glm::vec2 newPos{ m_pGameObject->GetTransform()->GetPosition() };

	switch (m_State)
	{
	case dae::AIComponent::State::Idle:
		switch (m_Direction)
		{
		case MovementDirection::Right:
			newPos.x += m_IdleSpeed * elapsedSec;
			if (newPos.x > m_Boundaries.y)
			{
				m_Direction = MovementDirection::Left;
				return;
			}
			break;
		case MovementDirection::Left:
			newPos.x -= m_IdleSpeed * elapsedSec;
			if (newPos.x < m_Boundaries.x)
			{
				m_Direction = MovementDirection::Right;
				return;
			}
			break;
		default:
			break;
		}
		break;
	case dae::AIComponent::State::Bombing:
		break;
	default:
		break;
	}

	m_pGameObject->GetTransform()->SetPosition(newPos);
}

void dae::AIComponent::Render(glm::vec2)
{
}
