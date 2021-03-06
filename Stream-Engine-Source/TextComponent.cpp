#include "MiniginPCH.h"
#include "TextComponent.h"

#include <SDL_ttf.h>
#include "Font.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Texture2D.h"

#include "ResourceManager.h"
#include "Renderer.h"

StreamEngine::TextComponent::TextComponent(std::weak_ptr<GameObject> pOwningGameObject, std::shared_ptr<RenderComponent> renderComponent)
	:BaseComponent(pOwningGameObject),
	m_pFont(nullptr),
	m_pRenderComponent(renderComponent),
	m_Color{ 255,255,255,255 },
	m_pText{},
	m_Size{ 20 },
	m_FontPath()
{
	
}

StreamEngine::TextComponent::TextComponent(const std::string& fontPath, std::weak_ptr<GameObject> pOwningGameObject, std::shared_ptr<RenderComponent> renderComponent)
	:TextComponent(pOwningGameObject, renderComponent)
{
	m_FontPath = fontPath;
	m_pFont = ResourceManager::GetInstance().LoadFont(fontPath, m_Size);
	if (m_pFont == nullptr)
	{
		throw std::exception{ "Font failed to initialize" };
	}
	CreateTextTexture();
}

void StreamEngine::TextComponent::SetText(const std::string& text)
{
	m_pText = text;
	CreateTextTexture();
}

void StreamEngine::TextComponent::SetSize(const int& size)
{
	m_Size = size;
	m_pFont = ResourceManager::GetInstance().LoadFont(m_FontPath, m_Size);
	CreateTextTexture();
}

void StreamEngine::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	CreateTextTexture();
}

void StreamEngine::TextComponent::CreateTextTexture() const
{
	if (m_pText.empty())
	{
		return;
	}
	SDL_Surface* pSurface = TTF_RenderText_Blended(m_pFont->GetFont(), m_pText.c_str(), m_Color);
	if (pSurface == nullptr)
	{
		throw std::runtime_error(std::string("Surface failed to initialize: ") + SDL_GetError());
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), pSurface);
	if (pTexture == nullptr)
	{
		throw std::runtime_error(std::string("SDL_Texture from surface failed to initialize: ") + SDL_GetError());
	}

	SDL_FreeSurface(pSurface);
	m_pRenderComponent->SetTexture(std::make_shared<Texture2D>(pTexture));
}
