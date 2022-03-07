#pragma once
#include <SDL_stdinc.h>
#include <XInput.h>
#include "Singleton.h"

namespace StreamEngine
{
	class Command;
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(const DWORD& button) const;
		void SetCommand(const std::shared_ptr<Command>& command);
		void SetAmountOfPlayers(int amountOfPlayers);
		void ClearCommands();
		int GetAmountOfPlayers() const;

		void SetCommands(const std::vector<std::shared_ptr<Command>>& commands);
	private:
		XINPUT_STATE m_CurrentState{};
		std::vector<std::shared_ptr<Command>> m_Commands{};
		WORD m_LastButtons{};
		int m_AmountOfPlayers{ 1 };
	};

}
