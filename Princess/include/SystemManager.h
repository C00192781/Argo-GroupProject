#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include "ResourceManager.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "MovementSystem.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"

class SystemManager
{
public:

	RenderSystem *   RenderSystem;
	MovementSystem * MovementSystem;
	ControlSystem *  ControlSystem;

	void Update();

};
#endif

