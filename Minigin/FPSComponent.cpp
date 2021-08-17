#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "Font.h"

using namespace dae;

dae::FPSComponent::FPSComponent()
	: Component()
	, m_Frames{0}
	, m_FPS{60}
	, m_Elapsed{0.f}
	, m_pText{new TextComponent()}
{
}

dae::FPSComponent::~FPSComponent()
{
	delete m_pText;
	m_pText = nullptr;
}

void dae::FPSComponent::Update(float elapsedSec)
{
	m_Elapsed += elapsedSec;
	m_Frames++;
	if (m_Elapsed > 1.f)
	{
		m_FPS = m_Frames;
		m_Frames = 0;
		m_Elapsed -= 1.f;
	}
	m_pText->Update(elapsedSec);
}

void dae::FPSComponent::Render(glm::vec2 position)
{
	m_pText->SetFont(m_pFont);
	m_pText->SetText(std::to_string(m_FPS) + " FPS");
	m_pText->Render(position);
}

void dae::FPSComponent::SetFont(Font* pFont)
{
	m_pFont = pFont;
}
