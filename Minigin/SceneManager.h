#pragma once
#include "Singleton.h"
#include <map>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();

		Scene& CreateScene(const std::string& name);

		void SetCurrentScene(const std::string& name);

		void Update(float elapsedSec);
		void Render();
		void LateUpdate();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::string m_CurrentScene;

		std::map<std::string, Scene*> m_Scenes;
	};
}
