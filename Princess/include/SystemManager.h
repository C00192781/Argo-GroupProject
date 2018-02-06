#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include "ResourceManager.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "MovementSystem.h"
#include "RectangleComponent.h"
#include "SpriteComponent.h"
#include "ProjectileComponent.h"
#include "ProjectileSystem.h"
#include "CollisionSystem.h"

class SystemManager
{
public:

	RenderSystem *   RenderSystem;
	MovementSystem * MovementSystem;
	ControlSystem *  ControlSystem;
	ProjectileSystem * ProjectileSystem;
	CollisionSystem * CollisionSystem;

	void Update();

};
#endif

