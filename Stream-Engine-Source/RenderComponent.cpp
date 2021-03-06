#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "GameObject.h"

#include "Renderer.h"

StreamEngine::RenderComponent::RenderComponent(const std::weak_ptr<GameObject> pOwningGameObject)
	:BaseComponent{pOwningGameObject }
{
}

void StreamEngine::RenderComponent::Render() const
{
	if (m_pTexture)
	{
		BaseComponent::Render();
		Renderer::GetInstance().RenderTexture(*m_pTexture.get(), GetOwner()->GetTransform().GetPosition().x, GetOwner()->GetTransform().GetPosition().y);
	}
}

void StreamEngine::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_pTexture = texture;
}

std::shared_ptr<StreamEngine::Texture2D> StreamEngine::RenderComponent::GetTexture() const
{
	return m_pTexture;
}
