#ifndef _MENUSYSTEM_H
#define _MENUSYSTEM_H

#include "System.h"
#include "MenuComponent.h"
#include "ButtonComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"

class MenuSystem : public System
{
public:
	MenuSystem();
	~MenuSystem();
	void Update();
	void ChangeMenu(std::string ID);
	void SetUpMainMenu();
	void RemoveMenu();
private:
	int indexActiveMenu;
	std::string activeMenuID;
};


#endif
