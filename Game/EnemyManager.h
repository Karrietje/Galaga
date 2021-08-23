#pragma once
#include "Singleton.h"
#include "Utils.h"
#include <map>
#include <vector>
#include <string>
#pragma warning(push)
#pragma warning (disable:4201)
#include ".\glm\vec2.hpp"
#pragma warning(pop)

namespace dae
{
	class EnemyComponent;
	class PointComponent;
	class TextComponent;
	class Scene;
	class EnemyManager final : public Singleton<EnemyManager>
	{
	public:
		void LoadLevels(const std::string& fileName, Scene* pScene, bool isVersusMode);
		bool NextLevel();

		void SetPointObserver(PointComponent* pPointComponent, TextComponent* pTextComponent);
		void SetShotObserver();

		int GetEnemiesAlive() const;

		void Reset();
	private:
		friend class Singleton<EnemyManager>;
		EnemyManager() = default;

		int m_CurrentLevel;

		Scene* m_pScene;

		std::map<int, std::vector<EnemyComponent*>> m_Levels;
	};
}