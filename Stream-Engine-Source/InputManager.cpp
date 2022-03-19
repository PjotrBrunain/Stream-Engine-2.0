#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include <SDL.h>

#include "Backends/imgui_impl_sdl.h"

bool StreamEngine::InputManager::ProcessInput()
{
	// todo: read the input
	m_Controller.ProcessInput();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			for (const std::shared_ptr<Command> command : m_pCommands)
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
			for (const std::shared_ptr<Command> command : m_pCommands)
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
			for (const std::shared_ptr<Command> command : m_pCommands)
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
			for (const std::shared_ptr<Command> command : m_pCommands)
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

	auto buttonLambda = [this](const std::shared_ptr<Command> command)
	{
		if (command->IsOnRelease())
		{
			if (m_Controller.IsUp(command->GetControllerButton()))
			{
				if (command != nullptr)
				{
					command->Execute();
				}
			}
		}
		else
		{
			if (m_Controller.IsDown(command->GetControllerButton()))
			{
				if (command != nullptr)
				{
					command->Execute();
				}
			}
		}
	};

	for (const auto command : m_pCommands)
	{
		buttonLambda(command);
	}
	return true;
}

bool StreamEngine::InputManager::IsPressed(XinputController::ControllerButton button) const
{
	return m_Controller.IsPressed(button);
}

void StreamEngine::InputManager::AddCommand(std::shared_ptr<Command> pCommand)
{
	m_pCommands.push_back(pCommand);
}

void StreamEngine::InputManager::SetCommands(const std::vector<std::shared_ptr<Command>>& commands)
{
	m_pCommands = commands;
}
