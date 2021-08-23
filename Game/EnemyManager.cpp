#include "EnemyManager.h"
#include "GameObject.h"
#include "Components.h"
#include "GalagaComponents.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "PointObserver.h"
#include "ShotsObserver.h"
#include <fstream>
#include <iostream>
#include <algorithm>

void dae::EnemyManager::LoadLevels(const std::string& fileName, Scene* pScene, bool isVersusMode)
{
	bool tempVersusMode{ isVersusMode };
	m_pScene = pScene;
	std::ifstream input{};
	input.open(ResourceManager::GetInstance().GetDataPath() + fileName);
	if (!input.is_open())
	{
		std::cout << "Level file couldn't be opened\n";
	}

	int levelParsing{ 0 };
	glm::vec2 pos{ 100.f, 32.f };
	std::string line{};
	m_Levels.insert(std::make_pair(levelParsing, std::vector<EnemyComponent*>()));
	while (!input.eof())
	{
		std::getline(input, line);
		if (line.size() == 0)
		{
			levelParsing++;
			m_Levels.insert(std::make_pair(levelParsing, std::vector<EnemyComponent*>()));
			pos.x = 100.f;
			pos.y = 0.f;
			tempVersusMode = isVersusMode;
		}
		else
		{
			for (const char& enemy : line)
			{
				if (enemy != ' ')
				{
					GameObject* pEnemy = new GameObject;
					EnemyComponent* pEnemyComponent{};
					switch (enemy)
					{
					case 'B':
						if (tempVersusMode)
						{
							pEnemyComponent = new EnemyComponent(EnemyType::Boss, m_pScene, true);
							tempVersusMode = false;
						}
						else
							pEnemyComponent = new EnemyComponent(EnemyType::Boss, m_pScene);
						break;
					case 'G':
						pEnemyComponent = new EnemyComponent(EnemyType::Goei, m_pScene);
						break;
					case 'Z':
						pEnemyComponent = new EnemyComponent(EnemyType::Zako, m_pScene);
						break;
					}
					pEnemy->AddComponent(ComponentType::EnemyComponent, pEnemyComponent);
					pEnemy->GetTransform()->SetPosition(pos);
					m_pScene->Add(pEnemy, 4);
					m_Levels[levelParsing].push_back(pEnemyComponent);

					if (levelParsing != 0)
					{
						pEnemy->SetActive(false);
					}
				}

				pos.x += 32.f;
			}
		}
		pos.x = 100.f;
		pos.y += 32.f;
	}
}

bool dae::EnemyManager::NextLevel()
{
	if ((m_CurrentLevel + 1) == (int)m_Levels.size())
		return false;

	for (EnemyComponent* pEnemy : m_Levels.at(m_CurrentLevel))
		pEnemy->GetGameObject()->SetActive(false);

	m_CurrentLevel++;

	for (EnemyComponent* pEnemy : m_Levels.at(m_CurrentLevel))
		pEnemy->GetGameObject()->SetActive(true);

	return true;
}

void dae::EnemyManager::SetPointObserver(PointComponent* pPointComponent, TextComponent* pTextComponent)
{
	for (const std::pair<int, std::vector<EnemyComponent*>> level : m_Levels)
	{
		for (EnemyComponent* pEnemy : level.second)
		{
			PointObserver* pPointObserver = new PointObserver(pPointComponent, pTextComponent);
			pEnemy->GetGameObject()->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->AddObserver(pPointObserver);
		}
	}
}

void dae::EnemyManager::SetShotObserver()
{
	for (const std::pair<int, std::vector<EnemyComponent*>> level : m_Levels)
	{
		for (EnemyComponent* pEnemy : level.second)
		{
			ShotsObserver* pShotsObserver = new ShotsObserver();
			pEnemy->GetGameObject()->GetComponent<SubjectComponent>(ComponentType::SubjectComponent)->AddObserver(pShotsObserver);
		}
	}
}

int dae::EnemyManager::GetEnemiesAlive() const
{
	std::vector<EnemyComponent*> pEnemies{ m_Levels.at(m_CurrentLevel) };
	return (int)std::count_if(pEnemies.cbegin(), pEnemies.cend(), [](EnemyComponent* pEnemy) {return pEnemy->GetGameObject()->IsActive(); });
}

void dae::EnemyManager::Reset()
{
	for (EnemyComponent* pEnemy : m_Levels.at(m_CurrentLevel))
	{
		pEnemy->Reset();
	}
}
