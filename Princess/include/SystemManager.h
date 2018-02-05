#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include "ResourceManager.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "MovementSystem.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "AttributesComponent.h"
#include "HeartManagerComponent.h"
#include "AISystem.h"
#include "HealthSystem.h"

class SystemManager
{
public:

	RenderSystem *   RenderSystem;
	MovementSystem * MovementSystem;
	ControlSystem *  ControlSystem;
	AiSystem * AiSystem;
	HealthSystem * healthSystem;

	void Update();

private:
	bool flag = false;

};
#endif

