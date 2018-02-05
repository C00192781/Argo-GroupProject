#pragma once

#include "System.h"
#include "ControlComponent.h"
#include "MovementComponent.h"
#include "ProjectileComponent.h"

class ControlSystem : public System
{
public:
	ControlSystem(EventListener *e) { m_eventListener = e; };

	void Update();
private:

	EventListener *m_eventListener;
};