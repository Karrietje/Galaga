#include "EndScreenComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Components.h"
#include "Scene.h"
#include "ShotsObserver.h"
#include <string>

dae::EndScreenComponent::EndScreenComponent(Scene* pScene)
	: m_pScene{pScene}
{
}

void dae::EndScreenComponent::Initialize()
{
	GameObject* pGameObjectFont = new GameObject();
	TextureComponent* pTextureComponentBegin = new TextureComponent();
	pTextureComponentBegin->SetTexture("TitleScreen.png");
	pGameObjectFont->AddComponent(ComponentType::TextureComponent, pTextureComponentBegin);
	m_pScene->Add(pGameObjectFont, 0);

	GameObject* pGameObject = new GameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 50);
	auto textComp = new TextComponent();
	textComp->SetFont(font);
	textComp->SetText("Game Over!");
	pGameObject->AddComponent(ComponentType::TextComponent, textComp);
	m_pScene->Add(pGameObject, 1);
	pGameObject->GetTransform()->SetPosition(200.f, 200.f);

	pGameObject = new GameObject();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	m_pShotsFiredText = new TextComponent();
	m_pShotsFiredText->SetFont(font);
	m_pShotsFiredText->SetText("Shots Fired: 0");
	pGameObject->AddComponent(ComponentType::TextComponent, m_pShotsFiredText);
	m_pScene->Add(pGameObject, 1);
	pGameObject->GetTransform()->SetPosition(200.f, 250.f);

	pGameObject = new GameObject();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	m_pShotsHitText = new TextComponent();
	m_pShotsHitText->SetFont(font);
	m_pShotsHitText->SetText("Shots Hit: 0");
	pGameObject->AddComponent(ComponentType::TextComponent, m_pShotsHitText);
	m_pScene->Add(pGameObject, 1);
	pGameObject->GetTransform()->SetPosition(200.f, 274.f);

	pGameObject = new GameObject();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	m_pHitMissRatioText = new TextComponent();
	m_pHitMissRatioText->SetFont(font);
	m_pHitMissRatioText->SetText("Hit Miss Ratio: %100");
	pGameObject->AddComponent(ComponentType::TextComponent, m_pHitMissRatioText);
	m_pScene->Add(pGameObject, 1);
	pGameObject->GetTransform()->SetPosition(200.f, 298.f);
}

void dae::EndScreenComponent::Update(float)
{
	int shotsFired{ ShotsObserver::GetShotsFired() };
	int shotsHit{ ShotsObserver::GetShotsHit() };
	int ratio{ int((float(shotsHit) / float(shotsFired)) * 100) };
	if (shotsFired == 0)
		ratio = 0;

	m_pShotsFiredText->SetText("Shots Fired: " + std::to_string(ShotsObserver::GetShotsFired()));
	m_pShotsHitText->SetText("Shots Hit: " + std::to_string(ShotsObserver::GetShotsHit()));
	m_pHitMissRatioText->SetText("Hit Miss Ratio: %" + std::to_string(ratio));
}

void dae::EndScreenComponent::Render(glm::vec2)
{
}
