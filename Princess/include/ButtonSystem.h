#pragma once
#include "System.h"
#include "EventListener.h"
#include "ButtonComponent.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"

class ButtonSystem :
	public System
{
public:
	ButtonSystem(EventListener * e);
	~ButtonSystem();

	void Update();

	void LoadComponent();
	void UnloadComponent(int x);

private:

	EventListener * m_eventListener;
	std::vector<ButtonComponent*> m_buttonComponents;
	std::vector<PositionComponent*> m_positionComponents;
	std::vector<SpriteComponent*> m_spriteComponents;

};

