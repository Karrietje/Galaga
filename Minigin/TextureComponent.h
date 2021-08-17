#pragma once
#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		TextureComponent();
		virtual ~TextureComponent() override;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void SetTexture(const std::string& filename);
		void SetScale(float scale);
		
	private:
		Texture2D* m_pTexture;

		int m_Height; 
		int m_Width; 

		float m_Scale; 
	};
}