#pragma once
#include <Component.h>

namespace dae
{
    class Scene;
    class TextComponent;
    class EndScreenComponent final : public Component
    {
    public:
        EndScreenComponent(Scene* pScene);

        virtual void Initialize() override;
        virtual void Update(float elapsedSec) override;
        virtual void Render(glm::vec2 position) override;

    private:
        Scene* m_pScene;
        TextComponent* m_pShotsFiredText;
        TextComponent* m_pShotsHitText;
        TextComponent* m_pHitMissRatioText;
    };
}