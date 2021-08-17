#include "MiniginPCH.h"
#include "Component.h"

using namespace dae;

dae::Component::Component()
	: m_Initialized{ false } 
	, m_pGameObject{ nullptr }
{
}

void Component::SetGameObject(GameObject* pGameObject)
{
	m_pGameObject = pGameObject;
}

