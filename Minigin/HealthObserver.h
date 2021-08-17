#pragma once
#include "Observer.h"
#include <vector>

namespace dae
{
	class HealthComponent; 
	class GameObject;
	class HealthObserver final : public Observer
	{
	public:
		HealthObserver(HealthComponent* health, const std::vector<GameObject*>& pHearts);

		virtual void Notify(Event event) override;


	private:
		HealthComponent* m_pHealth; 
		std::vector<GameObject*> m_pHearts;
	};
}

