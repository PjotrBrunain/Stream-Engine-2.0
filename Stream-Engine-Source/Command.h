#pragma once
#include <SDL_stdinc.h>

namespace StreamEngine
{
	class Command
	{
	public:
		virtual ~Command() = default;

		Command(const Command&) = delete;
		Command(Command&&) noexcept = delete;
		Command& operator=(const Command&) = delete;
		Command& operator=(Command&&) noexcept = delete;

		virtual void Execute() = 0;

		bool IsOnRelease() const { return m_OnRelease; }
		DWORD GetControllerButton() const { return m_ControllerButton; }
		int GetControllerId() const { return m_ControllerId; }
		Sint32 GetKeyboardButton() const { return m_KeyBoardButton; }
		UINT8 GetMouseButton() const { return m_MouseButton; }
	private:
		bool m_OnRelease{};
		DWORD m_ControllerButton{};
		int m_ControllerId{};
		Sint32 m_KeyBoardButton{};
		UINT8 m_MouseButton{};

	protected:
		explicit Command(bool onRelease, DWORD controllerButton, int controllerId, Sint32 keyboardButton, UINT8 mouseButton)
			: m_OnRelease(onRelease),
			m_ControllerButton(controllerButton),
			m_ControllerId(controllerId),
			m_KeyBoardButton(keyboardButton),
			m_MouseButton(mouseButton) {}
	};
}
