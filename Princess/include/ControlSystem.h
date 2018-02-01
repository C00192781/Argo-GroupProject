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
	void updateVelocity(SDL_Event *e, int entityIndex, int ccKey, int mcKey);

	EventListener *m_eventListener;

};