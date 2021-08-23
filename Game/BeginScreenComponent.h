#pragma once
#include <Component.h>

namespace dae
{
	class Scene;
	class BeginScreenComponent final : public Component
	{
	public:
		BeginScreenComponent(Scene* pScene);

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

	private:
		Scene* m_pScene;
	};
}