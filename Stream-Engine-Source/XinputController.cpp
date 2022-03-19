#include "MiniginPCH.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include "XinputController.h"

class XinputController::XinputControllerImpl
{
public:
	void ProcessInput();
	bool IsPressed(ControllerButton button) const;
	bool IsDownThisFrame(ControllerButton button) const;
	bool IsUpThisFrame(ControllerButton button) const;

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_LastState{};
	int m_ControllerIdx{};

	DWORD m_ButtonsPressedThisFrame{};
	DWORD m_ButtonsReleasedThisFrame{};
};

bool XinputController::XinputControllerImpl::IsDownThisFrame(ControllerButton button) const
{
	return m_ButtonsPressedThisFrame & DWORD(button);
}

bool XinputController::XinputControllerImpl::IsUpThisFrame(ControllerButton button) const
{
	return m_ButtonsReleasedThisFrame & DWORD(button);
}

void XinputController::XinputControllerImpl::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	const DWORD dwResult = XInputGetState(m_ControllerIdx, &m_CurrentState);
	if (dwResult == ERROR_SUCCESS)
	{
		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_LastState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
		m_LastState = m_CurrentState;
	}
}

bool XinputController::XinputControllerImpl::IsPressed(ControllerButton button) const
{
	return m_CurrentState.Gamepad.wButtons & DWORD(button);
}

XinputController::XinputController()
	:pImpl(new XinputControllerImpl{})
{
}

XinputController::~XinputController()
{
	delete pImpl;
}

void XinputController::ProcessInput()
{
	pImpl->ProcessInput();
}

bool XinputController::IsDown(ControllerButton button) const
{
	return pImpl->IsDownThisFrame(button);
}

bool XinputController::IsUp(ControllerButton button) const
{
	return pImpl->IsUpThisFrame(button);
}

bool XinputController::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(button);
}
