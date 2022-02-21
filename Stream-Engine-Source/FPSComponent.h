#pragma once
#include "BaseComponent.h"

namespace StreamEngine
{
	class TextComponent;

	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(std::weak_ptr<GameObject> pOwningGameObject, std::shared_ptr<TextComponent> pTextComponent);
		~FPSComponent() override = default;


		void Update(float deltaTime) override;


		FPSComponent(const FPSComponent&) = delete;
		FPSComponent(FPSComponent&&) noexcept = delete;
		FPSComponent& operator=(const FPSComponent&) = delete;
		FPSComponent& operator=(FPSComponent&&) noexcept = delete;
	private:
		std::shared_ptr<TextComponent> m_pTextComponent{};
		float m_AccumulatedTime{};
		const float m_UpdateTimeSec{};
	};
}
