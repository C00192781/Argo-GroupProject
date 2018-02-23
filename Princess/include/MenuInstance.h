#ifndef _MENUSYSTEM_H
#define _MENUSYSTEM_H

#include "Instance.h"
#include "MenuComponent.h"
#include "ButtonComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "TextComponent.h"
#include "StateManager.h"
#include "EventListener.h"

class MenuInstance : public Instance
{
public:
	MenuInstance(SystemManager* s, EventListener * listerner , StateManager * state);
	MenuInstance(SystemManager* s, EventListener * listerner, StateManager * state, std::vector<Entity*> players);
	~MenuInstance();
	void Load();
	void Update();
	void LoadComponent();
	void UnloadComponent(int x);

private:
	EventListener * m_eventListener;
	StateManager * m_states;
	SystemManager * m_system;
	std::vector<Entity*> m_players;
	int m_timer = 0;

	void connect();
};
#endif
