#ifndef _SYSTEMMANAGER_H
#define _SYSTEMMANAGER_H

#include <iostream>

#include "MovementSystem.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "ButtonSystem.h"
#include "AttackSystem.h"
#include "CollisionSystem.h"
#include "AISystem.h"
#include "SoundSystem.h"
#include "HealthSystem.h"
#include "TextRenderSystem.h"

//#include "Quad.h"
//#include "Entity.h"
//#include "EventListener.h"
//#include "BattleMap.h"
//#include "PositionComponent.h"
//#include "SpriteComponent.h"
//#include "ProjectileSystem.h"
//#include "ProjectileComponent.h"
//#include "CollisionComponent.h"

//#include "AttributesComponent.h"
//#include "TextComponent.h"

//#include "ButtonComponent.h"

//#include "HeartComponent.h"

//#include "Princess.h"

//#include "LTimer.h"
//#include "WorldMap.h"
//#include "DungeonMap.h"
//#include "TownInstance.h"
//#include "AchievementHandler.h"


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

	void Update(float deltaTime);

private:
	bool flag = false;
	//RenderSystem *   RenderSystem;
	//MovementSystem * MovementSystem;
	//ControlSystem *  ControlSystem;

	void Update();
};
#endif

