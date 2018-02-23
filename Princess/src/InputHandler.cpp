#include "InputHandler.h"

void InputHandler::ControllerInit()
{
	SDL_Init(SDL_INIT_JOYSTICK);
	MaxJoysticks = SDL_NumJoysticks();

	if (MaxJoysticks > 0)
	{
		m_eventListener->controllerActivated = true;
	}
	else
	{
		m_eventListener->controllerActivated = false;
	}
	ControllerIndex = 0;
	for (int JoystickIndex = 0; JoystickIndex < MaxJoysticks; ++JoystickIndex)
	{
		if (!SDL_IsGameController(JoystickIndex))
		{
			continue;
		}
		if (ControllerIndex >= MAX_CONTROLLERS)
		{
			break;
		}
		gameController[ControllerIndex] = SDL_GameControllerOpen(JoystickIndex);
		ControllerIndex++;
	}
}

void InputHandler::handleInput()
{
	for (int ControllerIndex = 0; ControllerIndex < MAX_CONTROLLERS; ControllerIndex++)
	{
		// if we disconnect the controller, we remove it 
		// we reactivate mouse & keyboard controls
		if (SDL_GameControllerGetAttached(gameController[ControllerIndex]) == false)
		{
			m_eventListener->controllerActivated = false;
			//SDL_GameControllerClose(gameController[ControllerIndex]);
		}
		if (m_eventListener->controllerActivated == true)
		{
			if (gameController[ControllerIndex] != 0 && SDL_GameControllerGetAttached(gameController[ControllerIndex]))
			{
				SDL_Joystick *joystick = SDL_GameControllerGetJoystick(gameController[ControllerIndex]);

				int16_t XAxisLeft = SDL_JoystickGetAxis(joystick, 0);
				int16_t YAxisLeft = SDL_JoystickGetAxis(joystick, 1);

				int16_t XAxisRight = SDL_JoystickGetAxis(joystick, 3);
				int16_t YAxisRight = SDL_JoystickGetAxis(joystick, 4);

				float rightJoystickAngle = atan2(YAxisRight, XAxisRight) * (180 / 3.142) + 90;

				m_eventListener->LeftTrigger = SDL_GameControllerGetAxis(gameController[ControllerIndex], SDL_CONTROLLER_AXIS_TRIGGERLEFT);
				m_eventListener->RightTrigger = SDL_GameControllerGetAxis(gameController[ControllerIndex], SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

				m_eventListener->LeftStickX = XAxisLeft;
				m_eventListener->LeftStickY = YAxisLeft;
				m_eventListener->RightStick = rightJoystickAngle;
				m_eventListener->AButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_A);
				m_eventListener->BButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_B);
				m_eventListener->YButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_Y);
				m_eventListener->XButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_X);
				m_eventListener->LeftShoulder = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
				m_eventListener->RightShoulder = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
				m_eventListener->UpButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_UP);
				m_eventListener->DownButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				m_eventListener->LeftButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_LEFT);
				m_eventListener->RightButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				m_eventListener->StartButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_START);
				m_eventListener->BackButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_BACK);
				m_eventListener->GuideButton = SDL_GameControllerGetButton(gameController[ControllerIndex], SDL_CONTROLLER_BUTTON_GUIDE);
			}
		}
	}


	while (SDL_PollEvent(m_event))
	{
		switch (m_event->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (!m_event->key.repeat)
			{
				switch (m_event->button.button)
				{
				case SDL_BUTTON_LEFT:
					m_eventListener->LeftClick = true;
					break;
				case SDL_BUTTON_RIGHT:
					m_eventListener->RightClick = true;
					break;

				default:
					break;
				}
				break;
			}

		case SDL_MOUSEBUTTONUP:
			if (!m_event->key.repeat)
			{
				switch (m_event->button.button)
				{
				case SDL_BUTTON_LEFT:
					m_eventListener->LeftClick = false;
					break;
				case SDL_BUTTON_RIGHT:
					m_eventListener->RightClick = false;
					break;

				default:
					break;
				}
				break;
			}

		case SDL_KEYDOWN:
			if (!m_event->key.repeat)
			{
				switch (m_event->key.keysym.sym)
				{
				case SDLK_w:
					m_eventListener->W = true;
					break;

				case SDLK_a:
					m_eventListener->A = true;
					break;

				case SDLK_s:
					m_eventListener->S = true;
					break;

				case SDLK_d:
					m_eventListener->D = true;
					break;

				case SDLK_r:
					m_eventListener->roll = true;
					break;

				case SDLK_v:
					m_eventListener->roll = true;
					break;

				case SDLK_ESCAPE:
					m_eventListener->Escape = true;
					break;

				case SDLK_SPACE:
					m_eventListener->Space = true;
					break;

				default:
					break;
				}
				break;
			}

		case SDL_KEYUP:
			if (!m_event->key.repeat)
			{
				switch (m_event->key.keysym.sym)
				{
				case SDLK_w:
					m_eventListener->W = false;
					break;

				case SDLK_a:
					m_eventListener->A = false;
					break;

				case SDLK_s:
					m_eventListener->S = false;
					break;

				case SDLK_d:
					m_eventListener->D = false;
					break;

				case SDLK_r:
					m_eventListener->roll = false;
					break;
				case SDLK_v:
					m_eventListener->roll = false;
					break;

				case SDLK_ESCAPE:
					m_eventListener->Escape = false;
					break;

				case SDLK_SPACE:
					m_eventListener->Space = false;
					break;

				default:
					break;
				}
				break;
			}
		}
	}
}