#pragma once
#include <Component.h>

namespace dae
{
    class MissileComponent final : public Component
    {
    public:
        MissileComponent();

        virtual void Initialize() override;
        virtual void Update(float elapsedSec) override;
        virtual void Render(glm::vec2 position) override;

        virtual void Trigger(Tag triggerTag, GameObject* pGameObject) override;
    
    private:
        bool m_IsHit;
        float m_ShotSpeed;
    };
}