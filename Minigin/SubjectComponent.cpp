#include "MiniginPCH.h"
#include "SubjectComponent.h"
#include "Observer.h"

dae::SubjectComponent::SubjectComponent()
	:m_pObservers{}
{
}

dae::SubjectComponent::~SubjectComponent()
{
	for (size_t i{}; i < m_pObservers.size(); i++)
	{
		delete m_pObservers[i];
		m_pObservers[i] = nullptr;
	}
}

void dae::SubjectComponent::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver); 
	pObserver->SetSubjectComponent(this); 
}

void dae::SubjectComponent::Notify(Event event)
{
	for (Observer* pObserver : m_pObservers)
	{
		pObserver->Notify(event); 
	}
}

void dae::SubjectComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::SubjectComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position);
}
