#include "MiniginPCH.h"
#include "BaseComponent.h"

StreamEngine::BaseComponent::BaseComponent(std::weak_ptr<GameObject> pOwningGameObject)
	:m_pOwningGameObject(pOwningGameObject)
{
}