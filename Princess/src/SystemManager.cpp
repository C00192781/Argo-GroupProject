#include "SystemManager.h"

SystemManager::SystemManager(ResourceManager *resourceManager, SDL_Renderer* gameRenderer, EventListener *listener, std::vector<Entity*>* projectiles)
{
	

}

void SystemManager::Update(float deltaTime)
{
	if (controlSystem->Active()) { controlSystem->Update(); }
	if (movementSystem->Active()) { movementSystem->Update(deltaTime); }
	if (renderSystem->Active()) { renderSystem->Update(); }
	if (attackSystem->Active()) { attackSystem->Update(deltaTime); }
	if (aiSystem->Active()) { aiSystem->Update(deltaTime); }
	if (collisionSystem->Active()) { collisionSystem->Update(); }






	//std::vector<Entity*>* projectiles = ProjectileSystem->getEntities();
	//
	//if (CollisionSystem->Active()) { CollisionSystem->Update(); }
	//if (MovementSystem->Active()) { MovementSystem->Update(deltaTime); }
	//if (ControlSystem->Active())
	//{
	//	ControlSystem->Update();
	//	ControlSystem->getSystemEntities(projectiles);
	//}
	//
	//if (renderSystem->Active()) { renderSystem->Update(); }
	//if (AiSystem->Active()) { AiSystem->Update(deltaTime); }
	//if (ProjectileSystem->Active()) { ProjectileSystem->Update(); }
	//if (healthSystem->Active()) { healthSystem->Update(deltaTime); }

}


//void SystemManager::Update()
//{
//	if (MovementSystem->Active()) { MovementSystem->Update(); }
//	if (ControlSystem->Active()) { ControlSystem->Update(); }
//	if (RenderSystem->Active()) { RenderSystem->Update(); }
//}