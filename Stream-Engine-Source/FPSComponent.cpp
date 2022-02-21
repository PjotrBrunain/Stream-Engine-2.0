#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "TextComponent.h"

StreamEngine::FPSComponent::FPSComponent(std::weak_ptr<GameObject> pOwningGameObject, std::shared_ptr<TextComponent> pTextComponent)
	:BaseComponent(pOwningGameObject),
	m_pTextComponent{ pTextComponent },
	m_AccumulatedTime{},
	m_UpdateTimeSec{ 1 }
{
}

void StreamEngine::FPSComponent::Update(float deltaTime)
{
	m_AccumulatedTime += deltaTime;
	if (m_AccumulatedTime >= m_UpdateTimeSec * 1000)
	{
		m_pTextComponent->SetText(std::to_string(int(1 / deltaTime * 1000)));
		m_AccumulatedTime = 0;
	}
}
