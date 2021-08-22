#include "AIComponent.h"
#include "GameObject.h"
#include "Components.h"
#include "MissileManager.h"

dae::AIComponent::AIComponent(EnemyType type)
	: m_MissileTime{1.5f}
	, m_BombingTime{2.f}
	, m_ChangeDirectionTime{0.5f}
	, m_TractorBeamTime{5.f}
	, m_IdleSpeed{32.f}
	, m_BombingSpeed{96.f}
	, m_DiagonalBombingSpeed{96.f / sqrtf(2)}
	, m_SpriteWidth{32.f}
	, m_Boundaries{}
	, m_ScreenBoundaries{0.f, 640.f}
	, m_Type{type}
	, m_AIState{AIState::Idle}
	, m_Direction{MovementDirection::Right}
	, m_OriginalDirection{MovementDirection::Right}
{
}

void dae::AIComponent::Initialize()
{
	m_Boundaries.x = m_pGameObject->GetTransform()->GetPosition().x;
	m_Boundaries.y = m_Boundaries.x + (5 * m_SpriteWidth);

	m_OriginalPosition = m_pGameObject->GetTransform()->GetPosition();

	MissileManager::GetInstance().SubscribeGameObject(m_pGameObject, true);

	m_MoveTimer -= ((2 * (std::rand() % 10)) + 10);
}

void dae::AIComponent::Update(float elapsedSec)
{
	m_MoveTimer += elapsedSec;
	glm::vec2 newPos{};

	float deltaPos{ m_IdleSpeed * elapsedSec };
	switch (m_OriginalDirection)
	{
	case MovementDirection::Right:
		m_OriginalPosition.x += deltaPos;
		if (m_OriginalPosition.x > m_Boundaries.y)
		{
			m_OriginalDirection = MovementDirection::Left;
			m_OriginalPosition -= deltaPos;
		}
		break;
	case MovementDirection::Left:
		m_OriginalPosition.x -= deltaPos;
		if (m_OriginalPosition.x < m_Boundaries.x)
		{
			m_OriginalDirection = MovementDirection::Right;
			m_OriginalPosition += deltaPos;
		}
		break;
	default:
		break;
	}

	switch (m_AIState)
	{
	case dae::AIComponent::AIState::Idle:
		newPos = Idle(elapsedSec);
		break;
	case dae::AIComponent::AIState::Bombing:
		switch (m_Type)
		{
		case EnemyType::Zako:
			newPos = ZakoBombing(elapsedSec);
			break;
		case EnemyType::Goei:
			newPos = GoeiBombing(elapsedSec);
			break;
		case EnemyType::Boss:
			newPos = GoeiBombing(elapsedSec);
			break;
		default:
			break;
		}
		MissileHandling(elapsedSec);
		break;
	case dae::AIComponent::AIState::Moving:
		newPos = GoeiBombing(elapsedSec);
		break;
	case dae::AIComponent::AIState::TractorBeam:
		newPos = BossTractorBeam(elapsedSec);
		break;
	case dae::AIComponent::AIState::Returning:
		newPos = Returning(elapsedSec);
		break;
	default:
		break;
	}

	m_pGameObject->GetTransform()->SetPosition(newPos);
}

void dae::AIComponent::Render(glm::vec2)
{

}

void dae::AIComponent::Trigger(Tag triggerTag, GameObject*)
{
	switch (triggerTag)
	{
	case Tag::Front:
		m_AIState = AIState::Returning;
		break;
	case Tag::TractorBeamFront:
		if (m_AIState == AIState::Moving)
		{
			m_MoveTimer = 0.f;
			m_AIState = AIState::TractorBeam;
		}
		break;
	default:
		break;
	}
}

dae::AIComponent::AIState dae::AIComponent::GetState() const
{
	return m_AIState;
}

MovementDirection dae::AIComponent::GetDirection() const
{
	if ((m_AIState == AIState::Idle) || (m_AIState == AIState::TractorBeam))
		return MovementDirection::Up;

	return m_Direction;
}

void dae::AIComponent::MissileHandling(float elapsedSec)
{
	m_MissileTimer += elapsedSec;
	if (m_MissileTimer >= m_MissileTime)
	{
		m_MissileTimer = 0.f;
		MissileManager::GetInstance().ShootMissile(m_pGameObject);
	}
}

glm::vec2 dae::AIComponent::Idle(float)
{
	if (m_MoveTimer > m_BombingTime)
	{
		m_MoveTimer = 0.f;
		if ((rand() % 20) == 0)
		{
			if (m_Type == EnemyType::Boss)
			{
				if ((rand() % 2) == 0)
				{
					m_AIState = AIState::Moving;
					m_Direction = MovementDirection::Down;
					return m_OriginalPosition;
				}
			}
			m_AIState = AIState::Bombing;
			m_Direction = MovementDirection::Down;
			m_MissileTimer = 0.f;
		}
	}
	return m_OriginalPosition;
}

glm::vec2 dae::AIComponent::ZakoBombing(float elapsedSec)
{
	glm::vec2 newPos{ m_pGameObject->GetTransform()->GetPosition() };
	switch (m_Direction)
	{
	case MovementDirection::Right:
		newPos.x += m_BombingSpeed * elapsedSec;
		if (newPos.x >= (m_ScreenBoundaries.y - (2 * m_SpriteWidth)))
		{
			m_Direction = MovementDirection::DownRight;
			m_MoveTimer = 0.f;
			break;
		}
		else if (m_MoveTimer > m_ChangeDirectionTime)
		{
			m_MoveTimer = 0.f;
			switch (rand() % 2)
			{
			case 0:
				m_Direction = MovementDirection::DownRight;
				break;
			default:
				break;
			}
		}
		break;
	case MovementDirection::DownRight:
		newPos.x += m_DiagonalBombingSpeed * elapsedSec;
		newPos.y += m_DiagonalBombingSpeed * elapsedSec;
		if (newPos.x >= (m_ScreenBoundaries.y - m_SpriteWidth))
		{
			m_Direction = MovementDirection::Down;
			m_MoveTimer = 0.f;
			break;
		}
		else if (m_MoveTimer > m_ChangeDirectionTime)
		{
			m_MoveTimer = 0.f;
			switch (rand() % 4)
			{
			case 0:
				m_Direction = MovementDirection::Down;
				break;
			case 1:
				if (!(newPos.x >= (m_ScreenBoundaries.y - (2 * m_SpriteWidth))))
					m_Direction = MovementDirection::Right;
				else
					m_MoveTimer = m_ChangeDirectionTime;
				break;
			default:
				break;
			}
		}
		break;
	case MovementDirection::Down:
		newPos.y += m_BombingSpeed * elapsedSec;
		if (m_MoveTimer > m_ChangeDirectionTime)
		{
			m_MoveTimer = 0.f;
			switch (rand() % 3)
			{
			case 0:
				if (!(newPos.x <= (m_ScreenBoundaries.x + m_SpriteWidth)))
					m_Direction = MovementDirection::DownLeft;
				else
					m_MoveTimer = m_ChangeDirectionTime;
				break;
			case 1:
				if (!(newPos.x >= (m_ScreenBoundaries.y - (2 * m_SpriteWidth))))
					m_Direction = MovementDirection::DownRight;
				else
					m_MoveTimer = m_ChangeDirectionTime;
				break;
			default:
				break;
			}
		}
		break;
	case MovementDirection::DownLeft:
		newPos.x -= m_DiagonalBombingSpeed * elapsedSec;
		newPos.y += m_DiagonalBombingSpeed * elapsedSec;
		if (newPos.x <= m_ScreenBoundaries.x)
		{
			m_Direction = MovementDirection::Down;
			m_MoveTimer = 0.f;
			break;
		}
		else if (m_MoveTimer > m_ChangeDirectionTime)
		{
			m_MoveTimer = 0.f;
			switch (rand() % 4)
			{
			case 0:
				if (!(newPos.x <= (m_ScreenBoundaries.x + m_SpriteWidth)))
					m_Direction = MovementDirection::Left;
				else
					m_MoveTimer = m_ChangeDirectionTime;
				break;
			case 1:
				m_Direction = MovementDirection::Down;
				break;
			default:
				break;
			}
		}
		break;
	case MovementDirection::Left:
		newPos.x -= m_BombingSpeed * elapsedSec;
		if (newPos.x <= (m_ScreenBoundaries.x + m_SpriteWidth))
		{
			m_Direction = MovementDirection::DownLeft;
			m_MoveTimer = 0.f;
			break;
		}
		else if (m_MoveTimer > m_ChangeDirectionTime)
		{
			m_MoveTimer = 0.f;
			switch (rand() % 2)
			{
			case 0:
				m_Direction = MovementDirection::DownLeft;
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
	return newPos;
}

glm::vec2 dae::AIComponent::GoeiBombing(float elapsedSec)
{
	glm::vec2 newPos{ m_pGameObject->GetTransform()->GetPosition() };
	switch (m_Direction)
	{
	case MovementDirection::Right:
		newPos.x += m_BombingSpeed * elapsedSec;
		if (newPos.x >= (m_ScreenBoundaries.y - (2 * m_SpriteWidth)))
		{
			m_Direction = MovementDirection::DownRight;
			m_MoveTimer = 0.f;
			break;
		}
		else if (m_MoveTimer > m_ChangeDirectionTime)
		{
			m_MoveTimer = 0.f;
			switch (rand() % 3)
			{
			case 0:
			case 1:
				m_Direction = MovementDirection::DownRight;
				break;
			default:
				break;
			}
		}
		break;
	case MovementDirection::DownRight:
		newPos.x += m_DiagonalBombingSpeed * elapsedSec;
		newPos.y += m_DiagonalBombingSpeed * elapsedSec;
		if (newPos.x >= (m_ScreenBoundaries.y - m_SpriteWidth))
		{
			m_Direction = MovementDirection::Down;
			m_MoveTimer = 0.f;
			break;
		}
		else if (m_MoveTimer > m_ChangeDirectionTime)
		{
			m_MoveTimer = 0.f;
			switch (rand() % 5)
			{
			case 0:
			case 1:
				m_Direction = MovementDirection::Down;
				break;
			case 2:
			case 3:
				if (!(newPos.x >= (m_ScreenBoundaries.y - (2 * m_SpriteWidth))))
					m_Direction = MovementDirection::Right;
				else
					m_MoveTimer = m_ChangeDirectionTime;
				break;
			default:
				break;
			}
		}
		break;
	case MovementDirection::Down:
		newPos.y += m_BombingSpeed * elapsedSec;
		if (m_MoveTimer > m_ChangeDirectionTime)
		{
			m_MoveTimer = 0.f;
			switch (rand() % 5)
			{
			case 0:
			case 1:
				if (!(newPos.x <= (m_ScreenBoundaries.x + m_SpriteWidth)))
					m_Direction = MovementDirection::DownLeft;
				else
					m_MoveTimer = m_ChangeDirectionTime;
				break;
			case 2:
			case 3:
				if (!(newPos.x >= (m_ScreenBoundaries.y - (2 * m_SpriteWidth))))
					m_Direction = MovementDirection::DownRight;
				else
					m_MoveTimer = m_ChangeDirectionTime;
				break;
			default:
				break;
			}
		}
		break;
	case MovementDirection::DownLeft:
		newPos.x -= m_DiagonalBombingSpeed * elapsedSec;
		newPos.y += m_DiagonalBombingSpeed * elapsedSec;
		if (newPos.x <= m_ScreenBoundaries.x)
		{
			m_Direction = MovementDirection::Down;
			m_MoveTimer = 0.f;
			break;
		}
		else if (m_MoveTimer > m_ChangeDirectionTime)
		{
			m_MoveTimer = 0.f;
			switch (rand() % 5)
			{
			case 0:
			case 1:
				if (!(newPos.x <= (m_ScreenBoundaries.x + m_SpriteWidth)))
					m_Direction = MovementDirection::Left;
				else
					m_MoveTimer = m_ChangeDirectionTime;
				break;
			case 2:
			case 3:
				m_Direction = MovementDirection::Down;
				break;
			default:
				break;
			}
		}
		break;
	case MovementDirection::Left:
		newPos.x -= m_BombingSpeed * elapsedSec;
		if (newPos.x <= (m_ScreenBoundaries.x + m_SpriteWidth))
		{
			m_Direction = MovementDirection::DownLeft;
			m_MoveTimer = 0.f;
			break;
		}
		else if (m_MoveTimer > m_ChangeDirectionTime)
		{
			m_MoveTimer = 0.f;
			switch (rand() % 3)
			{
			case 0:
			case 1:
				m_Direction = MovementDirection::DownLeft;
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
	return newPos;
}

glm::vec2 dae::AIComponent::BossTractorBeam(float elapsedSec)
{
	glm::vec2 newPos{ m_pGameObject->GetTransform()->GetPosition() };

	m_MoveTimer += elapsedSec;
	if (m_MoveTimer >= m_TractorBeamTime)
	{
		m_Direction = MovementDirection::Down;
		m_AIState = AIState::Returning;
	}

	return newPos;
}

glm::vec2 dae::AIComponent::Returning(float elapsedSec)
{
	glm::vec2 newPos{ m_pGameObject->GetTransform()->GetPosition() };

	if (((m_Direction != MovementDirection::Left) && (m_Direction != MovementDirection::UpLeft) && (m_Direction != MovementDirection::Up) && (m_Direction != MovementDirection::UpRight) && (m_Direction != MovementDirection::Right)) && (abs(newPos.x - m_Boundaries.x) < abs(newPos.x - m_Boundaries.y)))
	{
		if (newPos.x < m_Boundaries.x)
			m_Direction = MovementDirection::UpRight;
		else
			m_Direction = MovementDirection::UpLeft;
	}
	else if(((m_Direction != MovementDirection::Left) && (m_Direction != MovementDirection::UpLeft) && (m_Direction != MovementDirection::Up) && (m_Direction != MovementDirection::UpRight) && (m_Direction != MovementDirection::Right)) && (abs(newPos.x - m_Boundaries.x) > abs(newPos.x - m_Boundaries.y)))
	{
		if (newPos.x < m_Boundaries.y)
			m_Direction = MovementDirection::UpRight;
		else
			m_Direction = MovementDirection::UpLeft;
	}

	switch (m_Direction)
	{
	case MovementDirection::Up:
		newPos.y -= m_BombingSpeed * elapsedSec;
		if (newPos.y <= (m_OriginalPosition.y + m_SpriteWidth))
		{
			if (m_OriginalPosition.x < newPos.x)
				m_Direction = MovementDirection::UpLeft;
			else
				m_Direction = MovementDirection::UpRight;
		}
		break;
	case MovementDirection::UpRight:
		newPos.x += m_DiagonalBombingSpeed * elapsedSec;
		newPos.y -= m_DiagonalBombingSpeed * elapsedSec;
		if (newPos.y > (m_OriginalPosition.y + m_SpriteWidth))
		{
			if (((abs(newPos.x - m_Boundaries.x) < abs(newPos.x - m_Boundaries.y)) && (newPos.x >= m_Boundaries.x)) || ((abs(newPos.x - m_Boundaries.x) > abs(newPos.x - m_Boundaries.y)) && (newPos.x >= m_Boundaries.y)))
				m_Direction = MovementDirection::Up;
		}
		else if ((newPos.y < (m_OriginalPosition.y + m_SpriteWidth)) && (newPos.y <= m_OriginalPosition.y))
			m_Direction = MovementDirection::Right;
		break;
	case MovementDirection::Right:
		newPos.x += m_BombingSpeed * elapsedSec;
		if (newPos.x >= m_OriginalPosition.x)
		{
			m_AIState = AIState::Idle;
			m_Direction = m_OriginalDirection;
			m_MoveTimer = -10.f;
			m_pGameObject->GetTransform()->SetPosition(m_OriginalPosition);
		}
		break;
	case MovementDirection::Left:
		newPos.x -= m_BombingSpeed * elapsedSec;
		if (newPos.x <= m_OriginalPosition.x)
		{
			m_AIState = AIState::Idle;
			m_Direction = m_OriginalDirection;
			m_MoveTimer = -10.f;
			m_pGameObject->GetTransform()->SetPosition(m_OriginalPosition);
		}
		break;
	case MovementDirection::UpLeft:
		newPos.x -= m_DiagonalBombingSpeed * elapsedSec;
		newPos.y -= m_DiagonalBombingSpeed * elapsedSec;

		if (newPos.y > (m_OriginalPosition.y + m_SpriteWidth))
		{
			if (((abs(newPos.x - m_Boundaries.x) < abs(newPos.x - m_Boundaries.y)) && (newPos.x <= m_Boundaries.x)) || ((abs(newPos.x - m_Boundaries.x) > abs(newPos.x - m_Boundaries.y)) && (newPos.x <= m_Boundaries.y)))
				m_Direction = MovementDirection::Up;
		}
		else if ((newPos.y < (m_OriginalPosition.y + m_SpriteWidth)) && (newPos.y <= m_OriginalPosition.y))
			m_Direction = MovementDirection::Left;
		break;
	default:
		break;
	}

	return newPos;
}
