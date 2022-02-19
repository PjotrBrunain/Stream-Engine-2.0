#pragma once
#include <functional>
struct SDL_Window;
namespace StreamEngine
{
	class Streamgin
	{
	public:
		Streamgin() = default;
		~Streamgin() = default;
		Streamgin(const Streamgin&) = delete;
		Streamgin(Streamgin&&) noexcept = delete;
		Streamgin& operator=(const Streamgin&) = delete;
		Streamgin& operator=(Streamgin&&) noexcept = delete;

		void Initialize();
		void LoadGame(const std::function<void()>& loadFunction) const;
		void Cleanup();
		void Run(const std::function<void()>& loadFunction);
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		float m_MsPerUpdate{ 20.f };
	};
}