#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "GameObject.h"
#include "RenderComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"

StreamEngine::TextureComponent::TextureComponent(const std::string& texturePath, std::weak_ptr<GameObject> pOwningGameObject, std::shared_ptr<RenderComponent> renderComponent)
	:BaseComponent(pOwningGameObject),
	m_pRenderComponent(renderComponent)
{
	renderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture(texturePath));
}