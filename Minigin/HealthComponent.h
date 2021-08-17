#pragma once
#include "Component.h"

namespace dae
{
	class HealthComponent : public Component
	{
	public:
		HealthComponent(int health); 
		
		inline int GetHealth() const; 

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

	private:
		int m_Health;

		void LoseHealth(); 
		
		//Healthobserver kan aan private functies
		friend class HealthObserver;

	};
}

inline int dae::HealthComponent::GetHealth() const
{
	return m_Health;
}


