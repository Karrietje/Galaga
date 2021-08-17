#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <map>
#include <memory>
#include <vector>
#include "Singleton.h"

class Command;
namespace dae
{
	enum class InputType
	{
		KeyDown,
		KeyUp,
		KeyHold
	};

	struct ControllerInput
	{
		//Which key 
		int keyboardInput;
		int controllerInput;
		InputType inputType;
		int player = 0;

		bool operator<(const ControllerInput& other) const
		{
			return controllerInput < other.controllerInput;
		}
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		void AddCommand(ControllerInput input, Command* command);

	private:
		XINPUT_KEYSTROKE m_ControllerState;
		std::multimap<ControllerInput, Command*> m_pControllerCommands;
		std::vector<int> m_PreviousPressedKeys;
	};
}

