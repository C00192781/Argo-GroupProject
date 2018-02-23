#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include "ResourceManager.h"
#include "renderSystem.h"
#include "ControlSystem.h"
#include "MovementSystem.h"
#include "AttackSystem.h"
#include "CollisionSystem.h"
#include "AISystem.h"
#include "CollisionSystem.h"
#include "HealthSystem.h"
#include "ButtonSystem.h"
#include "TextRenderSystem.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "ProjectileComponent.h"
#include "CollisionSystem.h"
#include "AttributesComponent.h"
#include "AISystem.h"
#include "CollisionSystem.h"
#include "HealthSystem.h"
#include "SoundComponent.h"
#include "SoundSystem.h"

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
	HealthSystem * healthSystem;
	AiSystem * aiSystem;
	ButtonSystem * buttonSystem;
	TextRenderSystem * textRenderSystem;
	SoundSystem * soundSystem;

	void Update(float deltaTime, std::vector<Entity*> players);

	void MassSelectiveClear();
	void MassClear();

private:
	bool flag = false;
};
#endif

