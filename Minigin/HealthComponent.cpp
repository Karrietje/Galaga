#include "MiniginPCH.h"
#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(int health)
	:m_Health{health}
{
}

void dae::HealthComponent::LoseHealth()
{
	m_Health -= 1; 
	if (m_Health < 0)
	{
		m_Health = 0; 
	}
}

void dae::HealthComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::HealthComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position);
}
