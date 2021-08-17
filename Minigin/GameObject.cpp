#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

using namespace dae;

dae::GameObject::GameObject(const std::string& name)
	: m_IsActive{true}
	, m_Name(name)
	, m_pChildren{}
{
	m_pTransform = new TransformComponent();
	m_pTransform->SetGameObject(this);
}

dae::GameObject::~GameObject()
{
	delete m_pTransform;
	m_pTransform = nullptr;

	for (std::pair<ComponentType, Component*> component : m_pComponents)
	{
		delete component.second;
		component.second = nullptr;
	}
	m_pComponents.clear();
}

void dae::GameObject::Trigger(Tag triggerTag, GameObject* pGameObject)
{
	for (std::pair<ComponentType, Component*> component : m_pComponents)
	{
		component.second->Trigger(triggerTag, pGameObject);
	}
}

void dae::GameObject::Update(float elapsedSec)
{
	if (!IsActive())
		return;

	for (std::pair<ComponentType, Component*> component : m_pComponents)
	{
		if (!component.second->IsInitialized())
			component.second->Initialize();

		component.second->Update(elapsedSec);
	}
}

void dae::GameObject::Render() const
{
	if (!IsActive())
		return;

	for (std::pair<ComponentType, Component*> component : m_pComponents)
	{
		component.second->Render(m_pTransform->GetWorldPosition());
	}
}

void dae::GameObject::AddComponent(ComponentType type, Component* pComponent)
{
	m_pComponents.insert(std::make_pair(type, pComponent));
	pComponent->SetGameObject(this);
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	if (pChild->GetParent())
		return;

	pChild->AddParent(this);
	m_pChildren.push_back(pChild);
}

inline GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

void GameObject::AddParent(GameObject* pParent)
{
	m_pParent = pParent;
}
