#include "InputHandler.h"

void InputHandler::ControllerInit()
{
	SDL_Init(SDL_INIT_JOYSTICK);
	MaxJoysticks = SDL_NumJoysticks();
	//std::cout << MaxJoysticks << std::endl;
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

void InputHandler::handleInput(SDL_Event &e)
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
				int xDir = 0;
				int yDir = 0;
				if (XAxisLeft < -8000)
				{
					xDir = -1;
				}
				else if (XAxisLeft > 8000)
				{
					xDir = 1;
				}
				else
				{
					xDir = 0;
				}

				if (YAxisLeft < -8000)
				{
					yDir = -1;
				}
				else if (YAxisLeft > 8000)
				{
					yDir = 1;
				}
				else
				{
					yDir = 0;
				}

				double leftJoystickAngle = atan2((double)yDir, (double)xDir) * (180.0 / M_PI);
				if (xDir == 0 && yDir == 0)
				{
					leftJoystickAngle = 0;
				}

				float rightJoystickAngle = atan2(YAxisRight, XAxisRight) + 3.14159265359 / 180 * 90;

				m_eventListener->LeftTrigger = SDL_GameControllerGetAxis(gameController[ControllerIndex], SDL_CONTROLLER_AXIS_TRIGGERLEFT);
				m_eventListener->RightTrigger = SDL_GameControllerGetAxis(gameController[ControllerIndex], SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

				m_eventListener->XStick = leftJoystickAngle;
				m_eventListener->YStick = rightJoystickAngle;
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

				/*	if (XAxisRight >= 0 && XAxisRight <= 32767)
				{
				if (YAxisRight >= -32767 && YAxisRight <= 0)
				{
				std::cout << "Top Right" << std::endl;
				}
				}
				if (XAxisRight >= 0 && XAxisRight <= 32767)
				{
				if (YAxisRight > 0 && YAxisRight <= 32767)
				{
				std::cout << "Bottom Right" << std::endl;
				}
				}
				if (XAxisRight >= -32767 && XAxisRight <= 0)
				{
				if (YAxisRight > 0 && YAxisRight <= 32767)
				{
				std::cout << "Bottom Left" << std::endl;
				}
				}
				if (XAxisRight >= -32767 && XAxisRight <= 0)
				{
				if (YAxisRight > -32767 && YAxisRight <= 0)
				{
				std::cout << "Top Left" << std::endl;
				}
				}*/
			}
		}
	}
	

	
	switch (e.type) 
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button)
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

	case SDL_MOUSEBUTTONUP:
		switch (e.button.button)
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

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) 
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

	case SDL_KEYUP:
		switch (e.key.keysym.sym) 
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