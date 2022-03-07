#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include <SDL.h>

#include "3rdParty/imgui-1.87/Backends/imgui_impl_sdl.h"


bool StreamEngine::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			for (const std::shared_ptr<Command> command : m_Commands)
			{
				if (!command->IsOnRelease())
				{
					if (command->GetKeyboardButton() == e.key.keysym.sym)
					{
						command->Execute();
					}
				}
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			for (const std::shared_ptr<Command> command : m_Commands)
			{
				if (!command->IsOnRelease())
				{
					if (command->GetMouseButton() == e.button.button)
					{
						command->Execute();
					}
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
			for (const std::shared_ptr<Command> command : m_Commands)
			{
				if (command->IsOnRelease())
				{
					if (command->GetKeyboardButton() == e.key.keysym.sym)
					{
						command->Execute();
					}
				}
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			for (const std::shared_ptr<Command> command : m_Commands)
			{
				if (command->IsOnRelease())
				{
					if (command->GetMouseButton() == e.button.button)
					{
						command->Execute();
					}
				}
			}
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	for (int i = 0; i < m_AmountOfPlayers; ++i)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		const DWORD dwResult = XInputGetState(0, &m_CurrentState);
		if (dwResult == ERROR_SUCCESS)
		{
			if (m_CurrentState.Gamepad.wButtons != m_LastButtons)
			{
				auto buttonLambda = [this](const std::shared_ptr<Command>& button)
				{
					if (button->IsOnRelease())
					{
						if ((m_LastButtons & DWORD(button->GetControllerButton())) == DWORD(button->GetControllerButton()) && !IsPressed(button->GetControllerButton()))
						{
							if (button != nullptr)
							{
								button->Execute();
							}
						}
					}
					else
					{
						if (IsPressed(button->GetControllerButton()))
						{
							if (button != nullptr)
							{
								button->Execute();
							}
						}
					}
				};

				for (const std::shared_ptr<Command>& flexiCommand : m_Commands)
				{
					if (flexiCommand->GetControllerId() == i)
					{
						buttonLambda(flexiCommand);
					}
				}
				m_LastButtons = m_CurrentState.Gamepad.wButtons;
			}
		}
	}

	return true;
}

bool StreamEngine::InputManager::IsPressed(const DWORD& button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

void StreamEngine::InputManager::SetCommand(const std::shared_ptr<Command>& command)
{
	m_Commands.push_back(command);
}

void StreamEngine::InputManager::SetAmountOfPlayers(int amountOfPlayers)
{
	m_AmountOfPlayers = amountOfPlayers;
}

void StreamEngine::InputManager::ClearCommands()
{
	m_Commands.clear();
}

int StreamEngine::InputManager::GetAmountOfPlayers() const
{
	return m_AmountOfPlayers;
}

void StreamEngine::InputManager::SetCommands(const std::vector<std::shared_ptr<Command>>& commands)
{
	m_Commands = commands;
}

