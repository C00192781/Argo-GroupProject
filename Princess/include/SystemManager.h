#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include "ResourceManager.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "MovementSystem.h"
#include "AttackSystem.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "AISystem.h"

class SystemManager
{
public:

	RenderSystem *   RenderSystem;
	MovementSystem * MovementSystem;
	ControlSystem *  ControlSystem;
	AttackSystem* AttackSystem;
	AiSystem * AiSystems;

	void Update(float deltaTime);

private:
	bool flag = false;

};
#endif

