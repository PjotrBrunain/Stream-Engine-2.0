#pragma once
#include <SDL.h>
#include "BaseComponent.h"

namespace StreamEngine
{
	class RenderComponent;
	class Texture2D;
	class Font;

	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(std::weak_ptr<GameObject> pOwningGameObject, std::shared_ptr<RenderComponent> renderComponent);
		TextComponent(const std::string& fontPath, std::weak_ptr<GameObject> pOwningGameObject, std::shared_ptr<RenderComponent> renderComponent);
		~TextComponent() override = default;

		void SetText(const std::string& text);
		void SetSize(const int& size);
		void SetColor(const SDL_Color& color);

		TextComponent(const TextComponent&) = delete;
		TextComponent(TextComponent&&) noexcept = delete;
		TextComponent& operator=(const TextComponent&) = delete;
		TextComponent& operator=(TextComponent&&) noexcept = delete;

	private:
		std::shared_ptr<Font> m_pFont{};
		std::shared_ptr<RenderComponent> m_pRenderComponent{};
		SDL_Color m_Color{};
		std::string m_pText{};
		int m_Size{};
		std::string m_FontPath{};
		
		void CreateTextTexture() const;
	};
}