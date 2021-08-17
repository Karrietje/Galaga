#pragma once
#include <Component.h>

namespace dae
{
	class ZakoComponent final : public Component
	{
	public:
		ZakoComponent() = default;

		virtual void Initialize() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render(glm::vec2 position) override;

	private:
	};
}