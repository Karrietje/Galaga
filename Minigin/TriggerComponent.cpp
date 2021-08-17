#include "MiniginPCH.h"
#include "TriggerComponent.h"

dae::TriggerComponent::TriggerComponent(const glm::vec2& relativePosition, const glm::vec2& dimensions, Tag tag, std::vector<Tag> interactingTags)
	: m_Tag{tag}
	, m_InteractingTags{interactingTags}
	, m_RelativePosition{relativePosition}
	, m_Dimensions{dimensions}
{
}

void dae::TriggerComponent::Update(float)
{
}

void dae::TriggerComponent::Render(glm::vec2)
{
}