#pragma once
#include "SceneManager.h"
#include <map>

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		~Scene();

		void Add(GameObject* object, int level);

		void Initialize();
		void PostInitialize();
		void Update(float elapsedSec);
		void Render() const;
		void LateUpdate(); 

		inline bool IsInitialized() const;
		inline bool IsPostInitialized() const;

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		bool m_IsInitialized;
		bool m_IsPostInitialized;

		std::string m_Name;
		std::multimap<int,GameObject*> m_Objects{};

		static unsigned int m_IdCounter; 
	};

	inline bool dae::Scene::IsInitialized() const
	{
		return m_IsInitialized;
	}

	inline bool dae::Scene::IsPostInitialized() const
	{
		return m_IsPostInitialized;
	}
}
