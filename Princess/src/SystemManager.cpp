#include "SystemManager.h"

void SystemManager::Update(float deltaTime)
{
	std::vector<Entity*>* projectiles = ProjectileSystem->getEntities();

	if (CollisionSystem->Active()) { CollisionSystem->Update(); }
	if (MovementSystem->Active()) { MovementSystem->Update(deltaTime); }
	if (ControlSystem->Active())
	{
		ControlSystem->Update();
		ControlSystem->getSystemEntities(projectiles);
	}

	if (RenderSystem->Active()) { RenderSystem->Update(); }
	if (AiSystem->Active()) { AiSystem->Update(deltaTime); }
	if (ProjectileSystem->Active()) { ProjectileSystem->Update(); }
	if (healthSystem->Active()) { healthSystem->Update(deltaTime); }
}