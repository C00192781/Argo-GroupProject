#ifndef _MENUSYSTEM_H
#define _MENUSYSTEM_H

#include "System.h"
#include "MenuComponent.h"
#include "ButtonComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "StateManager.h"
#include "EventListener.h"

extern int GAME_SCALE;

class MenuSystem : public System
{
public:
	MenuSystem(EventListener * listerner , StateManager * state);
	~MenuSystem();
	void Update();
	void ChangeMenu(std::string ID);
	void SetUpMainMenu();
	void SetUpOptionsMenu();
	Entity* getMenu(std::string ID);
	void RemoveMenu(std::string ID);
	MenuComponent* GetMenuComponent(std::string ID);
	void LoadComponent();
	void UnloadComponent(int x);
private:
	int indexActiveMenu;
	std::string activeMenuID;
	int menuTimer;
	EventListener * m_eventListener;
	StateManager * m_states;
};


#endif
