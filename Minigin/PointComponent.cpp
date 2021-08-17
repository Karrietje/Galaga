#include "MiniginPCH.h"
#include "PointComponent.h"



void dae::PointComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::PointComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position);
}

void dae::PointComponent::AddPoints(int points)
{
	m_Points += points; 
}
