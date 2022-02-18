#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "FPSComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SDL.h"
#include "Stream-Engine.h"
#include "TextComponent.h"

void LoadFunction()
{
	auto& scene = StreamEngine::SceneManager::GetInstance().CreateScene("Demo");
	std::shared_ptr<StreamEngine::GameObject> fpsCounter{ std::make_shared<StreamEngine::GameObject>() };

	std::shared_ptr<StreamEngine::RenderComponent> pRenderComponent{ std::make_shared<StreamEngine::RenderComponent>(fpsCounter) };

	std::shared_ptr<StreamEngine::TextComponent> pTxtComponent{ std::make_shared<StreamEngine::TextComponent>("Lingua.otf",fpsCounter, pRenderComponent) };
	pTxtComponent->SetSize(26);
	pTxtComponent->SetColor({ 0,255,0,255 });
	const std::shared_ptr<StreamEngine::FPSComponent> pFPSComponent{ std::make_shared<StreamEngine::FPSComponent>(fpsCounter) };
	pTxtComponent->LinkText(pFPSComponent->GetTextLink());
	pTxtComponent->SetDoUpdate(true);

	fpsCounter->AddComponent(pRenderComponent);
	fpsCounter->AddComponent(pTxtComponent);
	fpsCounter->AddComponent(pFPSComponent);

	fpsCounter->GetTransform().SetPosition(0, 0, 0);

	scene.Add(fpsCounter);

	StreamEngine::SceneManager::GetInstance().SetActiveScene("Demo");
}

int main(int, char*[]) {
	StreamEngine::Streamgin engine{};
	engine.Run(LoadFunction);
    return 0;
}
