#include "SystemManager.h"

void SystemManager::Update(float deltaTime)
{
	if (ControlSystem->Active()) { ControlSystem->Update(); }
	if (MovementSystem->Active()) { MovementSystem->Update(deltaTime); }
	if (RenderSystem->Active()) { RenderSystem->Update(); }
	//if (AttackSystem->Active()) { AttackSystem->Update(); }
	if (AiSystem->Active()) { AiSystem->Update(deltaTime); }
	if (CollisionSystem->Active()) { CollisionSystem->Update(); }
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
	//if (RenderSystem->Active()) { RenderSystem->Update(); }
	//if (AiSystem->Active()) { AiSystem->Update(deltaTime); }
	//if (ProjectileSystem->Active()) { ProjectileSystem->Update(); }
	//if (healthSystem->Active()) { healthSystem->Update(deltaTime); }
}