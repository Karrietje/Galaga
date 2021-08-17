#include "MiniginPCH.h"
#include "PhysicsManager.h"
#include "TriggerComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <SDL.h>

void dae::PhysicsManager::Update(float)
{
	for (std::pair<Tag, std::vector<TriggerComponent*>> pairs : m_pTriggers)
	{
		for (TriggerComponent* pTrigger1 : pairs.second)
		{
			if (!pTrigger1->GetGameObject()->IsActive())
				continue;

			glm::vec2 trigger1Pos{ pTrigger1->GetGameObject()->GetTransform()->GetWorldPosition() + pTrigger1->GetRelativePosition() };
			glm::vec2 trigger1Dim{ pTrigger1->GetDimensions() };
			for (const Tag& interactingTag : pTrigger1->GetInteractingTags())
			{
				if (m_pTriggers.find(interactingTag) == m_pTriggers.end())
					continue;

				for (TriggerComponent* pTrigger2 : m_pTriggers[interactingTag])
				{
					if (!pTrigger2->GetGameObject()->IsActive())
						continue;

					glm::vec2 trigger2Pos{ pTrigger2->GetGameObject()->GetTransform()->GetWorldPosition() + pTrigger2->GetRelativePosition() };
					glm::vec2 trigger2Dim{ pTrigger2->GetDimensions() };

					float deltaX{};
					float deltaY{};
					if (trigger1Pos.x < trigger2Pos.x)
					{
						deltaX = trigger2Pos.x - trigger1Pos.x;
						if (trigger1Pos.y < trigger2Pos.y)
						{
							deltaY = trigger2Pos.y - trigger1Pos.y;

							if ((deltaX < trigger1Dim.x) && (deltaY < trigger1Dim.y))
								pTrigger1->GetGameObject()->Trigger(interactingTag, pTrigger2->GetGameObject());
						}
						else
						{
							deltaY = trigger1Pos.y - trigger2Pos.y;

							if ((deltaX < trigger1Dim.x) && (deltaY < trigger2Dim.y))
								pTrigger1->GetGameObject()->Trigger(interactingTag, pTrigger2->GetGameObject());
						}
					}
					else
					{
						deltaX = trigger1Pos.x - trigger2Pos.x;
						if (trigger1Pos.y < trigger2Pos.y)
						{
							deltaY = trigger2Pos.y - trigger1Pos.y;

							if ((deltaX < trigger2Dim.x) && (deltaY < trigger1Dim.y))
								pTrigger1->GetGameObject()->Trigger(interactingTag, pTrigger2->GetGameObject());
						}
						else
						{
							deltaY = trigger1Pos.y - trigger2Pos.y;

							if ((deltaX < trigger2Dim.x) && (deltaY < trigger2Dim.y))
								pTrigger1->GetGameObject()->Trigger(interactingTag, pTrigger2->GetGameObject());
						}
					}
				}
			}
		}
	}
}

void dae::PhysicsManager::Render() const
{
	if (!m_DrawDebug)
		return;

	SDL_Renderer* pRenderer{ Renderer::GetInstance().GetSDLRenderer() };

	Uint8 color[4]{};
	SDL_GetRenderDrawColor(pRenderer, &color[0], &color[1], &color[2], &color[3]);
	SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);

	glm::vec2 position{};
	glm::vec2 dimensions{};
	SDL_Rect rect{};
	
	for (std::pair<Tag, std::vector<TriggerComponent*>> tagTriggers : m_pTriggers)
	{
		for (TriggerComponent* pTrigger : tagTriggers.second)
		{
			if (!pTrigger->GetGameObject()->IsActive())
				continue;

			position = pTrigger->GetGameObject()->GetTransform()->GetWorldPosition();
			position += pTrigger->GetRelativePosition();

			dimensions = pTrigger->GetDimensions();

			rect.x = (int)position.x;
			rect.y = (int)position.y;
			rect.w = (int)dimensions.x;
			rect.h = (int)dimensions.y;

			SDL_RenderDrawRect(pRenderer, &rect);
		}
	}

	SDL_SetRenderDrawColor(pRenderer, color[0], color[1], color[2], color[3]);
}

dae::TriggerComponent* dae::PhysicsManager::CreateTriggerComponent(const glm::vec2& relativePosition, const glm::vec2& dimensions, Tag tag, std::vector<Tag> interactingTags)
{
	TriggerComponent* pTriggerComponent = new TriggerComponent(relativePosition, dimensions, tag, interactingTags);

	if (m_pTriggers.find(tag) == m_pTriggers.end())
	{
		m_pTriggers.insert(std::make_pair(tag, std::vector<TriggerComponent*>()));
	}
	m_pTriggers.at(tag).push_back(pTriggerComponent);
	
	return pTriggerComponent;
}

dae::PhysicsManager::PhysicsManager()
	: m_DrawDebug{true}
{
}
