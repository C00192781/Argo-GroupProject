#ifndef _EVENTLISTENER_H
#define _EVENTLISTENER_H

class EventListener
{
public:
	EventListener() {};
	// Mouse & Keyboard
	bool LeftClick = false;
	bool RightClick = false;
	bool Space = false;
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool Escape = false;


	// Controller
	// Triggers 
	// range of 0 to 32767
	int LeftTrigger = 0;
	int RightTrigger = 0;

	// Sticks 
	// range of -32767 to 32767
	//int16_t XStick = 0;
	//int16_t YStick = 0;
	int XStick = 0;
	float YStick = 0;

	// Buttons
	bool AButton = false;
	bool BButton = false;
	bool YButton = false;
	bool XButton = false;
	bool LeftShoulder = false;
	bool RightShoulder = false;
	bool UpButton = false;
	bool DownButton = false;
	bool LeftButton = false;
	bool RightButton = false;
	bool StartButton = false;
	bool BackButton = false;
	bool GuideButton = false;

	bool controllerActivated = false;

};
#endif
