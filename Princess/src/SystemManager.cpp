#include "SystemManager.h"

void SystemManager::Update(float deltaTime)
{
	std::vector<Entity*>* projectiles = ProjectileSystem->getEntities();
	//all fps loss estimations done with 51 characters on screen and no projectiles @ 60fps
	//if (CollisionSystem->Active()) { CollisionSystem->Update(); } //10fps~ THIS GUY'S FAULT, guts fps

	if (MovementSystem->Active()) { MovementSystem->Update(deltaTime); } //1

	//if (ControlSystem->Active()) //THIS GUY'S FAULT TOO halves fps
	//{
	//	ControlSystem->Update();
	//	ControlSystem->getSystemEntities(projectiles);
	//}

	//everything below this point is as expensive as everything above this point.
	if (RenderSystem->Active()) { RenderSystem->Update(); } //
	if (AiSystem->Active()) { AiSystem->Update(deltaTime); } //
	if (ProjectileSystem->Active()) { ProjectileSystem->Update(); } //
	if (healthSystem->Active()) { healthSystem->Update(); } //
}