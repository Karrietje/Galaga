#pragma once
#include "Singleton.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include ".\glm\vec2.hpp"
#pragma warning(pop)
#include "Utils.h"
#include <vector>
#include <map>

namespace dae
{
	class TriggerComponent;
	class PhysicsManager final : public Singleton<PhysicsManager>
	{
	public:
		void Update(float elapsedSec);
		void Render() const;

		TriggerComponent* CreateTriggerComponent(const glm::vec2& relativePosition, const glm::vec2& dimensions, Tag tag, std::vector<Tag> interactingTags);

	private:
		friend class Singleton<PhysicsManager>;
		PhysicsManager();

		bool m_DrawDebug;

		std::map<Tag, std::vector<TriggerComponent*>> m_pTriggers;
	};
}