#ifndef _MENUCOMPONENT_H
#define _MENUCOMPONENT_H
#include "Entity.h"
#include "Component.h"

class MenuComponent : public Component
{
private:
	std::vector<Entity*>* m_buttons;
public:
	MenuComponent() 
	{
		m_buttons = new std::vector<Entity*>();
		m_type = "MenuC";
	};
	~MenuComponent() 
	{
		delete m_buttons;
	};

	std::vector<Entity*>* Buttons() { return m_buttons; };
};

#endif