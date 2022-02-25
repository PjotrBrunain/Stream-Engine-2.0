#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "3rdParty/imgui-1.87/imgui.h"
#include "3rdParty/imgui-1.87/Backends/imgui_impl_opengl2.h"
#include "3rdParty/imgui-1.87/Backends/imgui_impl_sdl.h"

void StreamEngine::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	m_pWindow = window;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void StreamEngine::Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	//SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_Renderer);
}

void StreamEngine::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void StreamEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void StreamEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void StreamEngine::Renderer::RenderTexture(const Texture2D& spriteTexture, float dstX, float dstY, float srcX,
	float srcY, float srcWidth, float srcHeight) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(dstX);
	dst.y = static_cast<int>(dstY);
	dst.w = static_cast<int>(srcWidth);
	dst.h = static_cast<int>(srcHeight);
	SDL_Rect src;
	src.x = static_cast<int>(srcX);
	src.y = static_cast<int>(srcY);
	src.h = static_cast<int>(srcHeight);
	src.w = static_cast<int>(srcWidth);
	SDL_RenderCopy(GetSDLRenderer(), spriteTexture.GetSDLTexture(), &src, &dst);
}

void StreamEngine::Renderer::RenderTexture(const Texture2D& spriteTexture, float dstX, float dstY, float dstWidth,
	float dstHeight, float srcX, float srcY, float srcWidth, float srcHeight) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(dstX);
	dst.y = static_cast<int>(dstY);
	dst.w = static_cast<int>(dstWidth);
	dst.h = static_cast<int>(dstHeight);
	SDL_Rect src;
	src.x = static_cast<int>(srcX);
	src.y = static_cast<int>(srcY);
	src.h = static_cast<int>(srcHeight);
	src.w = static_cast<int>(srcWidth);
	SDL_RenderCopy(GetSDLRenderer(), spriteTexture.GetSDLTexture(), &src, &dst);
}
