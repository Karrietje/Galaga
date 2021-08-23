#include "BeginScreenComponent.h"
#include <Windows.h>
#include "../3rdParty/imgui-1.81/imgui.h"
#include "SceneManager.h"
#include "GalagaManagerComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Audio.h"
#include "AudioLocator.h"
#include "Components.h"
#include "Audio.h"
#include "AudioLocator.h"

dae::BeginScreenComponent::BeginScreenComponent(Scene* pScene)
	: m_pScene{pScene}
{
}

void dae::BeginScreenComponent::Initialize()
{
	GameObject* pGameObjectFont = new GameObject();
	TextureComponent* pTextureComponentBegin = new TextureComponent();
	pTextureComponentBegin->SetTexture("TitleScreen.png");
	pGameObjectFont->AddComponent(ComponentType::TextureComponent, pTextureComponentBegin);
	m_pScene->Add(pGameObjectFont, 0);

	AudioLocator::GetAudioSystem()->AddMusic(true, 0, "Sounds/MainMenu.mp3");
	AudioLocator::GetAudioSystem()->Play(0);
}

void dae::BeginScreenComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::BeginScreenComponent::Render(glm::vec2 position)
{
	UNREFERENCED_PARAMETER(position);

	//Making buttons with IMGUI
	static ImVec4 color = ImVec4(114.f / 255.f, 144.f / 255.f, 154.f / 255.f, 200.f / 255.f);
	ImGui::Begin("Window", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(230.f, 250.f));
	ImGui::Text("GameModes:");
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.f, 0.6f, 0.6f));
	if (ImGui::Button("Single Player", ImVec2(200.f, 50.f)))
	{
		auto& soloScene = SceneManager::GetInstance().CreateScene("GameSolo");

		GameObject* pGameObject = new GameObject();
		GalagaManagerComponent* pGameManager = new GalagaManagerComponent(GalagaManagerComponent::GameMode::Single, &soloScene);

		pGameObject->AddComponent(ComponentType::GalagaManagerComponent, pGameManager);
		soloScene.Add(pGameObject, 0);
		AudioLocator::GetAudioSystem()->StopAll();
		SceneManager::GetInstance().SetCurrentScene("GameSolo");		
	}
	if (ImGui::Button("Coop", ImVec2(200.f, 50.f)))
	{
		auto& coopScene = SceneManager::GetInstance().CreateScene("GameCoop");
		GameObject* pGameObject = new GameObject();
		GalagaManagerComponent* pGameManager = new GalagaManagerComponent(GalagaManagerComponent::GameMode::Coop, &coopScene);

		pGameObject->AddComponent(ComponentType::GalagaManagerComponent, pGameManager);
		coopScene.Add(pGameObject, 0);

		AudioLocator::GetAudioSystem()->StopAll();
		SceneManager::GetInstance().SetCurrentScene("GameCoop");
	}
	if (ImGui::Button("Versus", ImVec2(200.f, 50.f)))
	{
		auto& versusScene = SceneManager::GetInstance().CreateScene("GameVersus");
		GameObject* pGameObject = new GameObject();
		GalagaManagerComponent* pGameManager = new GalagaManagerComponent(GalagaManagerComponent::GameMode::Versus, &versusScene);

		pGameObject->AddComponent(ComponentType::GalagaManagerComponent, pGameManager);
		versusScene.Add(pGameObject, 0);

		AudioLocator::GetAudioSystem()->StopAll();
		SceneManager::GetInstance().SetCurrentScene("GameVersus");
	}
	ImGui::PopStyleColor(1);
	ImGui::End();
}
