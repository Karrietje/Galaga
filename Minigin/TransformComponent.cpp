#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"

using namespace dae;

TransformComponent::TransformComponent()
	: Component()
	, m_Position{0.f, 0.f}
{
}

glm::vec2 dae::TransformComponent::GetWorldPosition() const
{
	GameObject* pParent{ m_pGameObject->GetParent() };
	glm::vec2 position{ m_pGameObject->GetTransform()->GetPosition() };
	if (pParent)
	{
		position += pParent->GetTransform()->GetWorldPosition();
	}
	return position;
}

void TransformComponent::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void dae::TransformComponent::SetPosition(glm::vec2 pos)
{
	m_Position = pos;
}

void TransformComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void TransformComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position);
}
