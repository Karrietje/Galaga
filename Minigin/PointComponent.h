#pragma once
#include "Component.h"

namespace dae
{
	class PointComponent final : public Component
	{
	public:
		
		inline int GetPoints() const;

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

	private:
		int m_Points;

		void AddPoints(int points);

		//Healthobserver kan aan private functies
		friend class PointObserver;
	};
}

inline int dae::PointComponent::GetPoints() const
{
	return m_Points;
}