#pragma once
#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public Component
	{
	public:
		TextComponent();
		virtual ~TextComponent() override;
		
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
		
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void SetText(const std::string& text);
		void SetFont(Font* pFont);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Font* m_pFont;
		Texture2D* m_pTexture;
	};
}

