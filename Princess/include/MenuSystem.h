#ifndef _MENUSYSTEM_H
#define _MENUSYSTEM_H

#include "System.h"
#include "MenuComponent.h"
#include "ButtonComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "EventListener.h"

class MenuSystem : public System
{
public:
	MenuSystem(EventListener * listener);
	~MenuSystem();
	void Update();
	void ChangeMenu(std::string ID);
	void SetUpMainMenu();
	Entity* getMenu(std::string ID);
	void RemoveMenu(std::string ID);
	MenuComponent* GetMenuComponent(std::string ID);
private:
	int indexActiveMenu;
	std::string activeMenuID;
	EventListener *m_eventListener;
};


#endif
