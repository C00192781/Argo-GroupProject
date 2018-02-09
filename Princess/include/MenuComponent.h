#ifndef _MENUCOMPONENT_H
#define _MENUCOMPONENT_H
#include "Entity.h"
#include "Component.h"

class MenuComponent : public Component
{
private:
	std::vector<Entity*>* m_buttons;
	int m_selectedButtonIndex;
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

	int SelectedButtonIndex() { return m_selectedButtonIndex; };
	void SelectedButtonIndex(int selectedButtonIndex) { m_selectedButtonIndex = selectedButtonIndex; };
};

#endif