#include "MiniginPCH.h"
#include "RenderComponent.h"

StreamEngine::RenderComponent::RenderComponent(std::weak_ptr<GameObject> pOwningGameObject)
	:BaseComponent{ true, pOwningGameObject }
{
}

void StreamEngine::RenderComponent::Render() const
{
	BaseComponent::Render();
}

void StreamEngine::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_pTexture = texture;
}

std::shared_ptr<StreamEngine::Texture2D> StreamEngine::RenderComponent::GetTexture() const
{
	return m_pTexture;
}
