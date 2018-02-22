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
#include "MenuSystem.h"
//<<<<<<< HEAD

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

//=======
//#include "PositionComponent.h"
//#include "SpriteComponent.h"
//#include "ProjectileComponent.h"
//#include "CollisionSystem.h"
//#include "AttributesComponent.h"
//#include "HeartManagerComponent.h"
//#include "AISystem.h"
//#include "CollisionSystem.h"
//#include "HealthSystem.h"
//#include "MenuSystem.h"
//#include "SoundComponent.h"
//#include "SoundSystem.h"
//>>>>>>> master

class SystemManager
{
public:
	SystemManager() {}
	SystemManager(ResourceManager *resourceManager, SDL_Renderer* gameRenderer, EventListener *listener, std::vector<Entity*>* projectiles, StateManager* state);

	RenderSystem *   renderSystem;
	MovementSystem * movementSystem;
	ControlSystem *  controlSystem;
	AttackSystem* attackSystem;
	CollisionSystem *collisionSystem;
	HealthSystem * healthSystem;
	MenuSystem * menuSystem;
	AiSystem * aiSystem;
	ButtonSystem * buttonSystem;
	TextRenderSystem * textRenderSystem;
	SoundSystem * soundSystem;

	void Update(float deltaTime, std::vector<Entity*> players);


	//void Update(float deltaTime);

private:
	bool flag = false;
	//RenderSystem *   RenderSystem;
	//MovementSystem * MovementSystem;
	//ControlSystem *  ControlSystem;

	void Update() {};
};
#endif

