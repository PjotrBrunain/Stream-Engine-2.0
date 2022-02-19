#pragma once
#include "BaseComponent.h"
#include "string"

namespace StreamEngine
{
	class RenderComponent;
	class Texture2D;
	
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::string& texturePath, std::weak_ptr<GameObject> pOwningGameObject, std::shared_ptr<RenderComponent> renderComponent);
		~TextureComponent() override = default;

		TextureComponent(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) noexcept = delete;
		TextureComponent& operator=(const TextureComponent&) = delete;
		TextureComponent& operator=(TextureComponent&&) noexcept = delete;

	private:
		std::shared_ptr<RenderComponent> m_pRenderComponent;
	};
}
