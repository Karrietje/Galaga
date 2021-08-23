#include "MiniginPCH.h"
#include "Component.h"

using namespace dae;

dae::Component::Component()
	: m_Initialized{ false } 
	, m_IsActive{true}
	, m_pGameObject{ nullptr }
{
}

void dae::Component::SetActive(bool active)
{
	m_IsActive = active;
}

void Component::SetGameObject(GameObject* pGameObject)
{
	m_pGameObject = pGameObject;
}

void dae::Component::RootInitialize()
{
	Initialize();
	m_Initialized = true;
}

void dae::Component::RootPostInitialize()
{
	PostInitialize();
	m_PostInitialized = true;
}

void dae::Component::RootUpdate(float elapsedSec)
{
	if (m_IsActive)
		Update(elapsedSec);
}

void dae::Component::RootRender(glm::vec2 position)
{
	if (m_IsActive)
		Render(position);
}
