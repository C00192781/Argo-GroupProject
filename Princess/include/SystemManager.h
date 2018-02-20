#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include "ResourceManager.h"
#include "renderSystem.h"
#include "ControlSystem.h"
#include "MovementSystem.h"
#include "AttackSystem.h"
#include "ProjectileSystem.h"
#include "CollisionSystem.h"
#include "AISystem.h"
#include "CollisionSystem.h"
#include "HealthSystem.h"
#include "ButtonSystem.h"
#include "TextRenderSystem.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "ProjectileComponent.h"
#include "ProjectileSystem.h"
#include "CollisionSystem.h"
#include "AttributesComponent.h"
#include "AISystem.h"
#include "CollisionSystem.h"
#include "HealthSystem.h"

class SystemManager
{
public:
	SystemManager() {}
	SystemManager(ResourceManager *resourceManager, SDL_Renderer* gameRenderer, EventListener *listener, std::vector<Entity*>* projectiles);

	RenderSystem *   renderSystem;
	MovementSystem * movementSystem;
	ControlSystem *  controlSystem;
	AttackSystem* attackSystem;
	CollisionSystem *collisionSystem;
	ProjectileSystem * projectileSystem;
	HealthSystem * healthSystem;
	AiSystem * aiSystem;
	ButtonSystem * buttonSystem;
	TextRenderSystem * textRenderSystem;


	void Update(float deltaTime);

private:
	bool flag = false;
	//RenderSystem *   RenderSystem;
	//MovementSystem * MovementSystem;
	//ControlSystem *  ControlSystem;

	void Update();

};
#endif

