#pragma once
#include "Component.h"
#include <unordered_map>

struct SDL_Rect;
namespace dae
{
	class Texture2D; 
	class SpriteSheetComponent final : public Component
	{
	public:
		enum class SpriteState
		{
			Up,
			UpRight,
			Right,
			BottomRight,
			Bottom,
			BottomLeft,
			Left,
			UpLeft
		};

		struct SpriteInfo
		{
			int rows;
			int colums;
			int width;
			int height;

			std::unordered_map<SpriteState, std::pair<int, int>> SheetInfo; 
		};
		
		SpriteSheetComponent();
		~SpriteSheetComponent();

		SpriteSheetComponent(const SpriteSheetComponent& other) = delete;
		SpriteSheetComponent(SpriteSheetComponent&& other) = delete;
		SpriteSheetComponent& operator=(const SpriteSheetComponent& other) = delete;
		SpriteSheetComponent& operator=(SpriteSheetComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

		void SetSprite(const std::string& texturePath, const SpriteInfo& spriteInfo );
		void SetSpriteState(SpriteState state, bool resetRows = true);
		void SetFrameTime(float frameTime); 
		void SetScale(float scale); 

	private:
		int m_CurrentRow;
		int m_CurrentColumn; 
		
		float m_FrameTime; 
		float m_ElapsedTime; 
		float m_Scale; 

		int m_Width;
		int m_Height; 

		Texture2D* m_pTexture; 
		SDL_Rect* m_pSourceRect; 

		SpriteState m_CurrentSpriteState; 
		SpriteInfo m_SpriteInfo; 
	};
}

