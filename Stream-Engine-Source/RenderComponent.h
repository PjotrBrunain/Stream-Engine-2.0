#pragma once
#include "BaseComponent.h"

namespace StreamEngine
{
	class Texture2D;

	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(std::weak_ptr<GameObject> pOwningGameObject);
		~RenderComponent() override = default;

		RenderComponent(const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) noexcept = delete;
		RenderComponent& operator=(const RenderComponent&) = delete;
		RenderComponent& operator=(RenderComponent&&) noexcept = delete;

		void Render() const override;
		void SetTexture(std::shared_ptr<Texture2D> texture);
		std::shared_ptr<Texture2D> GetTexture() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}