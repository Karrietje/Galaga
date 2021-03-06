#pragma once
#include "Utils.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include ".\glm\vec2.hpp"
#pragma warning(pop)
#include <unordered_map>

namespace dae
{
	class GameObject;
	class Component
	{
	public:
		Component();
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Initialize() {};
		virtual void PostInitialize() {};
		virtual void Update(float elapsedSec) = 0;
		virtual void Render(glm::vec2 position) = 0;

		void SetActive(bool active);

		void SetGameObject(GameObject* pGameObject);
		inline GameObject* GetGameObject()const;

		virtual void Trigger(Tag, GameObject*) {};

	protected:
		bool m_Initialized;
		bool m_PostInitialized;
		bool m_IsActive;
		GameObject* m_pGameObject;

		friend class GameObject;
		void RootInitialize();
		void RootPostInitialize();
		void RootUpdate(float elapsedSec);
		void RootRender(glm::vec2 position);
	};

	inline GameObject* dae::Component::GetGameObject() const
	{
		return m_pGameObject;
	}
}

