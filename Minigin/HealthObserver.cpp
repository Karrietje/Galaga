#include "MiniginPCH.h"
#include "HealthObserver.h"
#include "HealthComponent.h"
#include "SubjectComponent.h"
#include "GameObject.h"

dae::HealthObserver::HealthObserver(HealthComponent* health, const std::vector<GameObject*>& pHearts)
	:m_pHealth{health}
	, m_pHearts{pHearts}
{
}

void dae::HealthObserver::Notify(Event event)
{
	switch (event)
	{
	case Event::Kill:
		if (m_pHealth)
		{
			//lock = temporary change to real pointer
			m_pHealth->LoseHealth();
			if (m_pHealth->GetHealth() != 0)
			{
				m_pHearts[m_pHealth->GetHealth()]->SetActive(false);
			}
			else
			{
				m_pSubject->GetGameObject()->SetActive(false);
				m_pHearts[m_pHealth->GetHealth()]->SetActive(false);
			}
		}
		break;
	}
}
