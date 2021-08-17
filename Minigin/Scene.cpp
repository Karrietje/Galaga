#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (auto& object : m_Objects)
	{
		delete object.second;
		object.second = nullptr;
	}
	m_Objects.clear(); 
}

void Scene::Add(GameObject* object, int level)
{
	m_Objects.insert(std::make_pair(level, object));
}

void Scene::Update(float elapsedSec)
{
	for(auto& object : m_Objects)
	{
		if (!object.second->GetDestroyed())
		{
			object.second->Update(elapsedSec);
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		if (!object.second->GetDestroyed())
		{
			object.second->Render();	
		}
	}
}

void dae::Scene::LateUpdate()
{
	auto it = m_Objects.begin();
	for (; it != m_Objects.end(); it++)
	{
		if (it->second->GetDestroyed())
		{
			auto tempIt = it;
			tempIt--; 
			delete it->second;
			m_Objects.erase(it); 
			it = tempIt;
		}
	}
}

