// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <Minigin.h>
#include "SceneManager.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GalagaManagerComponent.h"
#include "BeginScreenComponent.h"
#include "EndScreenComponent.h"
#include <vld.h>

using namespace dae;

void Initialize(); 

int main(int, char* []) 
{
	srand((unsigned int)time(nullptr));
	Minigin engine;
	engine.Initialize();

	Initialize(); 

	engine.Run();

	return 0;
}

void Initialize()
{
	//Begin scene with background
	auto& beginScene = SceneManager::GetInstance().CreateScene("BeginScene");

	GameObject* pGameObject = new GameObject();
	BeginScreenComponent* pBeginScreenComponent = new BeginScreenComponent(&beginScene);
	pGameObject->AddComponent(ComponentType::BeginScreenComponent, pBeginScreenComponent);
	beginScene.Add(pGameObject, 0);

	//End scene with background
	auto& endScene = SceneManager::GetInstance().CreateScene("EndScene");

	pGameObject = new GameObject();
	EndScreenComponent* pEndScreenComponent = new EndScreenComponent(&endScene);
	pGameObject->AddComponent(ComponentType::EndScreenComponent, pEndScreenComponent);
	endScene.Add(pGameObject, 0);

	SceneManager::GetInstance().SetCurrentScene("BeginScene");
}