#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float elapsedSec)
{
	m_Scenes[m_CurrentScene]->Update(elapsedSec);
}

void dae::SceneManager::Render()
{
	m_Scenes[m_CurrentScene]->Render();
}

void dae::SceneManager::LateUpdate()
{
	m_Scenes[m_CurrentScene]->LateUpdate();
}

dae::SceneManager::~SceneManager()
{
	for (std::pair<std::string, Scene*> scene : m_Scenes)
	{
		delete scene.second;
	}
	m_Scenes.clear();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_Scenes.insert(std::make_pair(name, scene));
	return *scene;
}

void dae::SceneManager::SetCurrentScene(const std::string& name)
{
	m_CurrentScene = name;
}