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
//#include "MenuSystem.h"
#include "NetworkSystem.h"
#include "SoundSystem.h"
#include "MementoCaretaker.h"

class SystemManager
{
public:
	SystemManager() {}
	SystemManager(ResourceManager *resourceManager, SDL_Renderer* gameRenderer, EventListener *listener, std::vector<Entity*>* projectiles, AStar* aStar, StateManager &state);

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
	NetworkSystem * networkSystem;
	MementoCaretaker * mementoSystem;

	void Update(float deltaTime, std::vector<Entity*> players);
	void Update() {};
	void MassSelectiveClear();
	void MassClear();
	//void Update(float deltaTime);

private:
	bool flag = false;
	//RenderSystem *   RenderSystem;
	//MovementSystem * MovementSystem;
	//ControlSystem *  ControlSystem;
};
#endif

