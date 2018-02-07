#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include "ResourceManager.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "MovementSystem.h"
#include "AttackSystem.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"<
#include "ProjectileComponent.h"
#include "ProjectileSystem.h"
#include "CollisionSystem.h"
#include "AttributesComponent.h"
#include "HeartManagerComponent.h"
#include "AISystem.h"
#include "CollisionSystem.h"
#include "HealthSystem.h"

class SystemManager
{
public:

	RenderSystem *   RenderSystem;
	MovementSystem * MovementSystem;
	ControlSystem *  ControlSystem;
	AttackSystem* AttackSystem;
	CollisionSystem *CollisionSystem;
	ProjectileSystem * ProjectileSystem;
	HealthSystem * healthSystem;
	AiSystem * AiSystem;

	void Update(float deltaTime);

private:
	bool flag = false;

};
#endif

