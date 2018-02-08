#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include "ResourceManager.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "MovementSystem.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "ProjectileComponent.h"
#include "ProjectileSystem.h"
#include "CollisionSystem.h"
#include "AttributesComponent.h"
#include "HeartManagerComponent.h"
#include "AISystem.h"
#include "HealthSystem.h"
#include "MenuSystem.h"

class SystemManager
{
public:

	RenderSystem *   RenderSystem;
	MovementSystem * MovementSystem;
	ControlSystem *  ControlSystem;
	ProjectileSystem * ProjectileSystem;
	CollisionSystem * CollisionSystem;
	HealthSystem * healthSystem;
	AiSystem * AiSystem;
	MenuSystem * menuSystem;

	void Update(float deltaTime);

private:
	bool flag = false;

};
#endif

