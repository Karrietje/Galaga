#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "SDL.h"

using namespace dae;

dae::TextureComponent::TextureComponent()
	:m_Scale{ 1.f }
{
}

dae::TextureComponent::~TextureComponent()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void dae::TextureComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::TextureComponent::Render(glm::vec2 position)
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y, (float)m_Width *  m_Scale, (float)m_Height * m_Scale);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr; 
	}
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);

	//Get width & height information from your texture. NULL = info we don't need.
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &m_Width, &m_Height); 
}

void dae::TextureComponent::SetScale(float scale)
{
	m_Scale = scale; 
}

