#ifndef _OPTIONSINSTANCE_H
#define _OPTIONSINSTANCE_H

#include "Instance.h"
#include "MenuComponent.h"
#include "ButtonComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "TextComponent.h"
#include "StateManager.h"
#include "EventListener.h"

class OptionsInstance : public Instance
{
public:
	OptionsInstance(SystemManager* s, EventListener * listerner, StateManager * state);
	~OptionsInstance();
	void Load();
	void Update();
	void LoadComponent();
	void UnloadComponent(int x);

private:
	EventListener * m_eventListener;
	StateManager * m_states;
	SystemManager * m_system;
	int m_timer = 0;
};
#endif
