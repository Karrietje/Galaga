#include "MiniginPCH.h"
#include "SpriteSheetComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL.h>
#include "Texture2D.h"

dae::SpriteSheetComponent::SpriteSheetComponent()
	:m_CurrentColumn{0}
	,m_CurrentRow{0}
	,m_CurrentSpriteState{SpriteState::BottomRight}
	, m_ElapsedTime{}
	, m_FrameTime{0.5f}
	, m_pTexture{}
	, m_pSourceRect{new SDL_Rect()}
	, m_Scale{1.f}
{
}

dae::SpriteSheetComponent::~SpriteSheetComponent()
{
	delete m_pTexture;
	delete m_pSourceRect; 

	m_pTexture = nullptr; 
	m_pSourceRect = nullptr;
}

void dae::SpriteSheetComponent::Update(float elapsedSec)
{
	m_ElapsedTime += elapsedSec; 
	//If the elapsedTime is higher than the frametime => How many rows you have, and you always loop to the begin of the row
	if (m_ElapsedTime >= m_FrameTime)
	{
		m_ElapsedTime -= m_FrameTime; 
		m_CurrentColumn++; 
		m_CurrentColumn %= m_SpriteInfo.SheetInfo[m_CurrentSpriteState].second; 
		m_pSourceRect->x = m_CurrentColumn * m_pSourceRect->w; 
	}
}

void dae::SpriteSheetComponent::Render(glm::vec2 position)
{
	//Check if you have a texture
	if (m_pTexture)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y, (float)m_Width * m_Scale, (float)m_Height * m_Scale, m_pSourceRect); 
	}
}

void dae::SpriteSheetComponent::SetSprite(const std::string& texturePath, const SpriteInfo& spriteInfo)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
	int width{}, height{};
	m_SpriteInfo = spriteInfo; 
	//Get width & height information from your texture. NULL = info we don't need.
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &width, &height);
	m_SpriteInfo.width = width; 
	m_SpriteInfo.height = height; 
	m_Width = width / m_SpriteInfo.colums; 
	m_Height = height / m_SpriteInfo.rows; 
	m_pSourceRect->x = 0; 
	m_pSourceRect->y = 0; 
	m_pSourceRect->w = m_SpriteInfo.width / m_SpriteInfo.colums;
	m_pSourceRect->h = m_SpriteInfo.height / m_SpriteInfo.rows; 
}

void dae::SpriteSheetComponent::SetSpriteState(SpriteState state, bool resetRows)
{
	m_CurrentSpriteState = state; 
	m_CurrentRow = m_SpriteInfo.SheetInfo[m_CurrentSpriteState].first;
	if (resetRows)
		m_CurrentColumn = 0;
	m_pSourceRect->x = 0; 
	m_pSourceRect->y = m_CurrentRow * m_pSourceRect->h; 
}

void dae::SpriteSheetComponent::SetFrameTime(float frameTime)
{
	m_FrameTime = frameTime; 
}

void dae::SpriteSheetComponent::SetScale(float scale)
{
	m_Scale = scale; 
}

