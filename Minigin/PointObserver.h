#pragma once
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class PointComponent;
	class PointObserver final : public Observer
	{
	public:
		PointObserver(PointComponent* point, TextComponent* pTextComponent);

		virtual void Notify(Event event) override;

	private:
		PointComponent* m_pPoints;
		TextComponent* m_pPointsText;
	};
}
