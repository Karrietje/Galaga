#pragma once
#include "Component.h"

namespace dae
{
    class Font;
    class TextComponent;
    class FPSComponent final : public Component
    {
    public:
        FPSComponent();
        virtual ~FPSComponent() override;

        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;

        virtual void Update(float elapsedSec) override;
        virtual void Render(glm::vec2 position) override;


        void SetFont(Font* pFont);

    private:
        int m_Frames;
        int m_FPS;
        float m_Elapsed;
        Font* m_pFont;
        TextComponent* m_pText;
    };
}