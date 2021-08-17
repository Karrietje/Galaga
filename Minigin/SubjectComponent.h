#pragma once
#include "Component.h"
#include "Utils.h"
#include <vector>

namespace dae
{
	class Observer; 
	class SubjectComponent : public Component
	{
	public:
		SubjectComponent(); 
		virtual ~SubjectComponent() override;
		
		SubjectComponent(const SubjectComponent& other) = delete;
		SubjectComponent(SubjectComponent&& other) = delete;
		SubjectComponent& operator=(const SubjectComponent& other) = delete;
		SubjectComponent& operator=(SubjectComponent&& other) = delete;
		
		void AddObserver(Observer* pObserver);
		void Notify(Event event); 

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;
	private:
		std::vector<Observer*> m_pObservers; 

	};

}
