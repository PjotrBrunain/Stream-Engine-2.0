#pragma once
#include "InputManager.h"

class Command
{
public:
	virtual ~Command() = default;

	Command(const Command&) = delete;
	Command(Command&&) noexcept = delete;
	Command& operator=(const Command&) = delete;
	Command& operator=(Command&&) noexcept = delete;

	virtual void Execute() const = 0;

	bool IsOnRelease() const { return m_OnRelease; }
	XinputController::ControllerButton GetControllerButton() const { return m_ControllerButton; }
	int GetControllerId() const { return m_ControllerId; }
	INT32 GetKeyboardButton() const { return m_KeyboardButton; }
	UINT8 GetMouseButton() const { return m_MouseButton; }

private:
	bool m_OnRelease{};
	XinputController::ControllerButton m_ControllerButton{};
	int m_ControllerId{};
	INT32 m_KeyboardButton{};
	UINT8 m_MouseButton{};

protected:
	explicit Command(bool onRelease, XinputController::ControllerButton controllerButton, int controllerId, INT32 keyboardButton, UINT8 mouseButton)
		: m_OnRelease(onRelease),
		m_ControllerButton(controllerButton),
		m_ControllerId(controllerId),
		m_KeyboardButton(keyboardButton),
		m_MouseButton(mouseButton){}
};
