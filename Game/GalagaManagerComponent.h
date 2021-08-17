#pragma once
#include <Component.h>

namespace dae
{
	class Scene;
	class GalagaManagerComponent : public Component
	{
	public:
		GalagaManagerComponent(Scene* pGalagaScene);

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;
	
	private:
		Scene* m_pGalagaScene;
	};
}