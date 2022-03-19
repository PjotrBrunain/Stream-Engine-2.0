#pragma once

class XinputController final
{
public:
	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		ButtonLeft = 0x0004,
		ButtonDown = 0x0002,
		ButtonRight = 0x0008,
		ButtonUp = 0x0001,
		ButtonMenu = 0x0010,
		//todo: add the other buttons
	};
	XinputController();
	~XinputController();

	void ProcessInput();
	bool IsDown(ControllerButton button) const;
	bool IsUp(ControllerButton button) const;
	bool IsPressed(ControllerButton button) const;

	XinputController(XinputController&&) = default;
	XinputController& operator=(XinputController&&) = default;


private:
	class XinputControllerImpl;
	XinputControllerImpl* pImpl;
};

