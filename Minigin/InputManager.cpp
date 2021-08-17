#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <algorithm>
#include "Command.h"


dae::InputManager::~InputManager()
{
	for (std::pair<ControllerInput, Command*> command : m_pControllerCommands)
	{
		delete command.second;
		command.second = nullptr;
	}
	m_pControllerCommands.clear();
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	std::vector<int> pressedKeys{};
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		for (std::pair<ControllerInput, Command*> command : m_pControllerCommands)
		{
			if (command.first.keyboardInput == e.key.keysym.sym)
			{
				pressedKeys.push_back(e.key.keysym.sym);
				switch (command.first.inputType)
				{
				case InputType::KeyDown:
					if ((e.type == SDL_KEYDOWN) && (std::find(m_PreviousPressedKeys.begin(), m_PreviousPressedKeys.end(), e.key.keysym.sym) == m_PreviousPressedKeys.end()))
 						command.second->Execute();
					break;
				case InputType::KeyHold:
					if ((e.type == SDL_KEYDOWN) && (std::find(m_PreviousPressedKeys.begin(), m_PreviousPressedKeys.end(), e.key.keysym.sym) != m_PreviousPressedKeys.end()))
						command.second->Execute();
					break;
				case InputType::KeyUp:
					if (e.type == SDL_KEYUP)
						command.second->Execute();
					break;
				default:
					break;
				}
			}
		}
	}
	m_PreviousPressedKeys = pressedKeys;

	//Wat in m_ControllerState zit leegmaken =>De grootte van input_State
	ZeroMemory(&m_ControllerState, sizeof(XINPUT_KEYSTROKE));

	for (int i{}; i < XUSER_MAX_COUNT; i++)
	{
		while (XInputGetKeystroke(i, 0, &m_ControllerState) == ERROR_SUCCESS)
		{
			for (std::pair<ControllerInput, Command*> command : m_pControllerCommands)
			{
				if ((command.first.player == i) && (command.first.controllerInput == m_ControllerState.VirtualKey))
				{
					switch (command.first.inputType)
					{
					case InputType::KeyDown:
						if (m_ControllerState.Flags & XINPUT_KEYSTROKE_KEYDOWN)
							command.second->Execute();
						break;
					case InputType::KeyHold:
						if (m_ControllerState.Flags & XINPUT_KEYSTROKE_REPEAT)
							command.second->Execute();
						break;
					case InputType::KeyUp:
						if (m_ControllerState.Flags & XINPUT_KEYSTROKE_KEYUP)
							command.second->Execute();
						break;
					default:
						break;
					}
				}
			}
			ZeroMemory(&m_ControllerState, sizeof(XINPUT_KEYSTROKE));
		}
	}

	return true;
}

void dae::InputManager::AddCommand(ControllerInput input, Command* command)
{
	m_pControllerCommands.insert(std::make_pair(input, command));
}
