#pragma once

#include "System.h"
#include "ControlComponent.h"
#include "MovementComponent.h"
#include "ProjectileComponent.h"

class ControlSystem : public System
{
public:
	ControlSystem(EventListener *e, InputHandler *input) { m_eventListener = e; m_input = input; };

	void Update();
private:

	void LoadComponent() {};
	void UnloadComponent(int x) {};

	EventListener *m_eventListener;
	InputHandler *m_input;
};