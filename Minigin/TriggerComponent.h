#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	class TriggerComponent final : public Component
	{
	public:
		TriggerComponent(const glm::vec2& relativePosition, const glm::vec2& dimensions, Tag tag, std::vector<Tag> interactingTags);

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		inline glm::vec2 GetRelativePosition() const;
		inline glm::vec2 GetDimensions() const;

		inline const Tag& GetTag() const;
		inline const std::vector<Tag>& GetInteractingTags() const;

	private:
		Tag m_Tag;
		std::vector<Tag> m_InteractingTags;

		glm::vec2 m_RelativePosition;
		glm::vec2 m_Dimensions;
	};

	inline glm::vec2 dae::TriggerComponent::GetRelativePosition() const
	{
		return m_RelativePosition;
	}

	inline glm::vec2 TriggerComponent::GetDimensions() const
	{
		return m_Dimensions;
	}
	inline const Tag& TriggerComponent::GetTag() const
	{
		return m_Tag;
	}
	inline const std::vector<Tag>& TriggerComponent::GetInteractingTags() const
	{
		return m_InteractingTags;
	}
}