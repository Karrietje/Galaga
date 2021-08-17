#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "TransformComponent.h"

using namespace dae;

dae::TextComponent::TextComponent()
	: m_NeedsUpdate{true}
	, m_Text{""}
	, m_pFont{}
	, m_pTexture{}
{
}

dae::TextComponent::~TextComponent()
{
	delete m_pFont;
	m_pFont = nullptr;

	delete m_pTexture;
	m_pTexture = nullptr;
}

void TextComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		delete m_pTexture;
		m_pTexture = new Texture2D(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render(glm::vec2 position)
{
	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y);
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetFont(Font* pFont)
{
	m_pFont = pFont;
}
