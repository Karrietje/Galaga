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
				std::cout << m_pSubject->GetGameObject()->GetName() << " loses HP!\n Remaining HP: " << m_pHealth->GetHealth() << '\n';
				m_pHearts[m_pHealth->GetHealth()]->SetActive(false);
			}
			else
			{
				std::cout << m_pSubject->GetGameObject()->GetName() << " died!\n";
				m_pSubject->GetGameObject()->SetActive(false);
				m_pHearts[m_pHealth->GetHealth()]->SetActive(false);
			}
		}
		break;
	}
}
