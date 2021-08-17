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

		void Update(float elapsedSec);
		void Render() const;
		void LateUpdate(); 

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::multimap<int,GameObject*> m_Objects{};

		static unsigned int m_IdCounter; 
	};

}
