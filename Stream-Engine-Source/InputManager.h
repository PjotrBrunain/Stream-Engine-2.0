#pragma once
#include <vector>

#include "Singleton.h"
#include "XinputController.h"

class Command;

namespace StreamEngine
{
	enum class ControllerButton;

	class InputManager : public Singleton<InputManager>
	{
	public:
		~InputManager() = default;
		bool ProcessInput();
		bool IsPressed(XinputController::ControllerButton button) const;

		void AddCommand(std::shared_ptr<Command> pCommand);
		void SetCommands(const std::vector<std::shared_ptr<Command>>& commands);
	private:
		XinputController m_Controller{};

		std::vector<std::shared_ptr<Command>> m_pCommands{};
	};
}
