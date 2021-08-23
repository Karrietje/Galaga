#include "GalagaManagerComponent.h"
#include "GameObject.h"
#include "GalagaComponents.h"
#include "SceneManager.h"
#include "Scene.h"
#include "MissileManager.h"
#include "Components.h"
#include "PhysicsManager.h"
#include "EnemyManager.h"
#include "Observers.h"
#include "ResourceManager.h"
#include "ShotsObserver.h"
#include "Audio.h"
#include "AudioLocator.h"

dae::GalagaManagerComponent::GalagaManagerComponent(GameMode gameMode, Scene* pScene)
	: m_MaxLives{3}
	, m_pLives{}
	, m_pScene{pScene}
	, m_GameMode{gameMode}
{
}

void dae::GalagaManagerComponent::Initialize()
{
	AudioLocator::GetAudioSystem()->AddMusic(true, 1, "Sounds/InGame.mp3");
	AudioLocator::GetAudioSystem()->AddSoundEffect(2, "Sounds/Shot.mp3");
	AudioLocator::GetAudioSystem()->AddSoundEffect(3, "Sounds/ZakoDead.mp3");
	AudioLocator::GetAudioSystem()->AddSoundEffect(4, "Sounds/GoeiDead.mp3");
	AudioLocator::GetAudioSystem()->AddSoundEffect(5, "Sounds/BossHit.mp3");
	AudioLocator::GetAudioSystem()->AddSoundEffect(6, "Sounds/BossDead.mp3");
	AudioLocator::GetAudioSystem()->AddSoundEffect(7, "Sounds/Dead.mp3");
	AudioLocator::GetAudioSystem()->Play(1);

	GameObject* pGameObjectFont = new GameObject();
	TextureComponent* pTextureComponentBegin = new TextureComponent();
	pTextureComponentBegin->SetTexture("Background.png");
	pGameObjectFont->AddComponent(ComponentType::TextureComponent, pTextureComponentBegin);
	m_pScene->Add(pGameObjectFont, 0);

	int nrShips{ 0 };
	GameObject* pSpaceship{};
	SpaceShipComponent* pSpaceshipComponent{};
	switch (m_GameMode)
	{
	case dae::GalagaManagerComponent::GameMode::Coop:
		pSpaceship = new GameObject();

		pSpaceshipComponent = new SpaceShipComponent(m_pScene, this, nrShips);
		nrShips++;
		pSpaceship->AddComponent(ComponentType::SpaceShipComponent, pSpaceshipComponent);

		m_pScene->Add(pSpaceship, 3);

		m_pSpaceShips.push_back(pSpaceship);
		pSpaceship->GetTransform()->SetPosition({ 304, 400 });
	case dae::GalagaManagerComponent::GameMode::Versus:
	case dae::GalagaManagerComponent::GameMode::Single:
		pSpaceship = new GameObject();

		pSpaceshipComponent = new SpaceShipComponent(m_pScene, this, nrShips);
		pSpaceship->AddComponent(ComponentType::SpaceShipComponent, pSpaceshipComponent);

		m_pScene->Add(pSpaceship, 3);

		m_pSpaceShips.push_back(pSpaceship);
		pSpaceship->GetTransform()->SetPosition({ 336, 400 });
		break;
	default:
		break;
	}

	GameObject* pBack = new GameObject();

	TriggerComponent* pBackTrigger = PhysicsManager::GetInstance().CreateTriggerComponent({ 0, 0 }, { 640, 1 }, Tag::Back, {});
	pBack->AddComponent(ComponentType::TriggerComponent, pBackTrigger);

	m_pScene->Add(pBack, 0);

	GameObject* pFront = new GameObject();

	TriggerComponent* pFrontTrigger = PhysicsManager::GetInstance().CreateTriggerComponent({ 0, 479 }, { 640, 1 }, Tag::Front, {});
	pFront->AddComponent(ComponentType::TriggerComponent, pFrontTrigger);

	m_pScene->Add(pFront, 0);

	GameObject* pTractorBeamFront = new GameObject();

	TriggerComponent* pTractorBeamFrontTrigger = PhysicsManager::GetInstance().CreateTriggerComponent({ 0, 320 }, { 640, 1 }, Tag::TractorBeamFront, {});
	pTractorBeamFront->AddComponent(ComponentType::TriggerComponent, pTractorBeamFrontTrigger);

	m_pScene->Add(pTractorBeamFront, 0);

	if (m_GameMode == GameMode::Versus)
		EnemyManager::GetInstance().LoadLevels("Levels/Levels.txt", m_pScene, true);
	else
		EnemyManager::GetInstance().LoadLevels("Levels/Levels.txt", m_pScene, false);

	for (int i{}; i < m_MaxLives; i++)
	{
		GameObject* pObject = new GameObject();
		TextureComponent* pTexture = new TextureComponent();
		pTexture->SetTexture("Sprites/Spaceship0.png");
		pTexture->SetScale(2.f);
		pObject->AddComponent(ComponentType::TextureComponent, pTexture);
		pObject->GetTransform()->SetPosition(10 + (i * 32.f), 440.f);
		m_pScene->Add(pObject, 5);
		m_pLives.push_back(pObject);
	}

	m_pHealthComponent = new HealthComponent(m_MaxLives);
	m_pGameObject->AddComponent(ComponentType::HealthComponent, m_pHealthComponent);
}

void dae::GalagaManagerComponent::PostInitialize()
{
	for (GameObject* pSpaceShip : m_pSpaceShips)
	{
		HealthObserver* healthObserver = new HealthObserver(m_pHealthComponent, m_pLives);
		SubjectComponent* pSubjectComponent = pSpaceShip->GetComponent<SubjectComponent>(ComponentType::SubjectComponent);
		pSubjectComponent->AddObserver(healthObserver);

		ShotsObserver* pShotsObserver = new ShotsObserver();
		pSubjectComponent->AddObserver(pShotsObserver);
	}

	GameObject* pGameObject = new GameObject();
	Font* font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	TextComponent* pTextComp = new TextComponent();
	pTextComp->SetFont(font);
	pTextComp->SetText("Points: ");
	pGameObject->AddComponent(ComponentType::TextComponent, pTextComp);
	m_pScene->Add(pGameObject, 1);
	pGameObject->GetTransform()->SetPosition(0.f, 0.f);

	pGameObject = new GameObject();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	pTextComp = new TextComponent();
	pTextComp->SetFont(font);
	pTextComp->SetText("0");
	pGameObject->AddComponent(ComponentType::TextComponent, pTextComp);
	m_pScene->Add(pGameObject, 1);
	pGameObject->GetTransform()->SetPosition(80.f, 0.f);

	PointComponent* pPointComp = new PointComponent();
	pGameObject->AddComponent(ComponentType::PointComponent, pPointComp);

	EnemyManager::GetInstance().SetPointObserver(pPointComp, pTextComp);
	EnemyManager::GetInstance().SetShotObserver();
}

void dae::GalagaManagerComponent::Update(float elapsedSec)
{
	AIComponent::UpdateOriginalPos(elapsedSec);
	if (EnemyManager::GetInstance().GetEnemiesAlive() == 0)
	{
		if (!EnemyManager::GetInstance().NextLevel())
		{
			GoToEndScene();
		}
	}

	if (m_pHealthComponent->GetHealth() == 0)
	{
		GoToEndScene();
	}
}

void dae::GalagaManagerComponent::Render(glm::vec2)
{
}

void dae::GalagaManagerComponent::SoftReset()
{
	glm::vec2 pos{};
	pos.y = m_pSpaceShips[0]->GetTransform()->GetPosition().y;
	pos.x = 320.f - (m_pSpaceShips.size() * 16.f);
	for (GameObject* pSpaceShip : m_pSpaceShips)
	{
		pSpaceShip->GetTransform()->SetPosition(pos);
		pos.x += 32.f;
	}

	EnemyManager::GetInstance().Reset();
	MissileManager::GetInstance().Reset();
}

void dae::GalagaManagerComponent::GoToEndScene()
{
	for (size_t i{}; i < m_pSpaceShips.size(); i++)
	{
		m_pSpaceShips[i]->SetActive(false);
	}
	AudioLocator::GetAudioSystem()->StopAll();
	AudioLocator::GetAudioSystem()->Play(0);
	SceneManager::GetInstance().SetCurrentScene("EndScene");
}
