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

	//if the button is selected
	bool m_selected;
	int m_timer;

public:
	ButtonComponent() 
	{ 
		m_activated = false;
		m_rect = SDL_Rect();
		m_type = "ButtonC";
		m_selected = false;
		m_timer = 0;
	};
	ButtonComponent(int posX, int posY, int width, int height)
	{
		m_type = "ButtonC";
		m_activated = false;
		m_rect.x = posX;
		m_rect.y = posY;
		m_rect.w = width;
		m_rect.h = height;
		m_timer = 0;

	};
	~ButtonComponent() {};

	bool Selected() { return m_selected; };
	void Selected(bool selected) { m_selected = selected; };

	bool Activated() { return m_activated; };
	void Activated(bool activated) { m_activated = activated; };

	int Timer() { return m_timer; };
	void Timer(int x) { m_timer = x; };

	SDL_Rect Rect() { return m_rect; };
	void Rect(SDL_Rect rect) { m_rect = rect; };

};
#endif