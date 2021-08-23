#pragma once
#include "Utils.h"
#include <unordered_map>
#include <vector>

namespace dae
{
	class Component;
	class TransformComponent;
	class Texture2D;
	class GameObject 
	{
	public:

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Initialize();
		void PostInitialize();
		void Update(float elapsedSec);
		void Render() const;

		void AddComponent(ComponentType type, Component* pComponent);
		void AddChild(GameObject* pChild);

		inline GameObject* GetParent() const;

		inline TransformComponent* GetTransform() const;
		
		template <typename T> 
		T* GetComponent(ComponentType type) const; 

		GameObject(const std::string& name = "");
		virtual ~GameObject();

		void Trigger(Tag triggerTag, GameObject* pGameObject);

		inline bool IsActive() const;
		inline void SetActive(bool active);

		inline std::string GetName() const; 

		inline void SetDestroy();
		inline bool GetDestroyed() const; 
	private:
		bool m_IsActive;
		bool m_NeedsDestroy;
		GameObject* m_pParent;
		std::vector<GameObject*> m_pChildren;

		TransformComponent* m_pTransform;
		std::unordered_multimap<ComponentType, Component*> m_pComponents;

		std::string m_Name; 

		void AddParent(GameObject* pParent);
	};

	inline TransformComponent* dae::GameObject::GetTransform() const
	{
		return m_pTransform;
	}

	//template: You decide where in the code what the class is you will work with. Returns pointer of type T->TextureComponent
	template <typename T> 
	T* GameObject::GetComponent(ComponentType type) const
	{
		T* pComponent{ static_cast<T*>(m_pComponents.find(type)->second) };
		return pComponent;
	}

	inline bool GameObject::IsActive() const
	{
		bool isActive{ m_IsActive };
		if (m_pParent)
		{
			isActive = m_IsActive && m_pParent->IsActive();
		}
		return isActive;
	}

	inline void GameObject::SetActive(bool active)
	{
		m_IsActive = active;
	}

	inline std::string dae::GameObject::GetName() const
	{
		return m_Name; 
	}

	inline void GameObject::SetDestroy()
	{
		m_NeedsDestroy = true; 
	}

	inline bool GameObject::GetDestroyed() const
	{
		return m_NeedsDestroy;
	}
}
