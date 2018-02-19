#ifndef _EVENTLISTENER_H
#define _EVENTLISTENER_H

class EventListener
{
public:
	EventListener() {};
	bool LeftClick = false;
	bool RightClick = false;
	bool Space = false;
	bool W = false;
	bool A = false;
	bool S = false;
	bool D = false;
	bool Escape = false;
	bool roll = false;
};
#endif
