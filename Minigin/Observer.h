#pragma once
#include "Utils.h"

namespace dae
{
	class SubjectComponent;
	class Observer
	{
	public:

		virtual ~Observer() = default;
		virtual void Notify(Event event) = 0;

		void SetSubjectComponent(SubjectComponent* subject) { m_pSubject = subject; }
	protected:
		SubjectComponent* m_pSubject; 
	};
}
