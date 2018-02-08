#ifndef _BUTTONCOMPONENT_H
#define _BUTTONCOMPONENT_H
#include "Component.h"

class ButtonComponent : public Component
{
private:
	//if the button has been activated or not
	bool m_activated;

	//The button's dimensions
	SDL_Rect m_rect;

public:
	ButtonComponent() 
	{ 
		m_activated = false;
		m_rect = SDL_Rect();
		m_type = "ButtonC";
	};
	ButtonComponent(int posX, int posY, int width, int height)
	{
		m_rect.x = posX;
		m_rect.y = posY;
		m_rect.w = width;
		m_rect.h = height;
	};
	~ButtonComponent() {};

	bool Activated() { return m_activated; };
	void Activated(bool activated) { m_activated = activated; };

	SDL_Rect Rect() { return m_rect; };
	void Rect(SDL_Rect rect) { m_rect = rect; };

};



#endif