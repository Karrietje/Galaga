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
	case Event::ZakoKill:
		m_pPoints->AddPoints(50);
		break;
	case Event::ZakoDivingKill:
		m_pPoints->AddPoints(100);
		break;
	case Event::GoeiKill:
		m_pPoints->AddPoints(80);
		break;
	case Event::GoeiDivingKill:
		m_pPoints->AddPoints(160);
		break;
	case Event::BossKill:
		m_pPoints->AddPoints(150);
		break;
	case Event::BossDivingKill:
		m_pPoints->AddPoints(400);
		break;
	default:
		break;
	}
	m_pPointsText->SetText(std::to_string(m_pPoints->GetPoints()));
}
