#pragma once

#include "System.h"
#include "ControlComponent.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "InputHandler.h"

class ControlSystem : public System
{
public:
	ControlSystem(EventListener *e) { m_eventListener = e; };

	void Update();
private:
	void updateVelocity(int entityIndex, int mcKey);
	void updatePosition(int entityIndex, int mcKey, int pcKey);

	EventListener *m_eventListener;

};