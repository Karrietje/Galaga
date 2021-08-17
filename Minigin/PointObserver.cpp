#include "MiniginPCH.h"
#include "PointObserver.h"
#include "PointComponent.h"
#include "SubjectComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::PointObserver::PointObserver(PointComponent* point, TextComponent* pTextComponent)
	:m_pPoints{point}
	, m_pPointsText(pTextComponent)
{
}

void dae::PointObserver::Notify(Event event)
{
	switch (event)
	{
	case Event::ColorChange:
		if (m_pPoints)
		{
			m_pPoints->AddPoints(25);
			std::cout << m_pSubject->GetGameObject()->GetName() << " got 25 points!\n" << "Total points: " << m_pPoints->GetPoints() << " in total!\n";
		}
		break;
	case Event::KillByFlyingDisc:
		if (m_pPoints)
		{
			m_pPoints->AddPoints(500);
			std::cout << m_pSubject->GetGameObject()->GetName() << " got 500 points!\n" << "Total points: " << m_pPoints->GetPoints() << " in total!\n";
		}
		break;
	case Event::RemainingDisc:
		if (m_pPoints)
		{
			m_pPoints->AddPoints(50);
			std::cout << m_pSubject->GetGameObject()->GetName() << " got 50 points!\n" << "Total points: " << m_pPoints->GetPoints() << " in total!\n";
		}
		break;
	case Event::CatchingSlickSam:
		if (m_pPoints)
		{
			m_pPoints->AddPoints(300);
			std::cout << m_pSubject->GetGameObject()->GetName() << " got 300 points!\n" << "Total points: " << m_pPoints->GetPoints() << " in total!\n";
		}
		break;
	default:
		break;
	}
	m_pPointsText->SetText(std::to_string(m_pPoints->GetPoints()));
}
