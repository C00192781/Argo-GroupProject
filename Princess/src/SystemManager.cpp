#include "SystemManager.h"

void SystemManager::Update()
{

	std::vector<Entity*>* projectiles = ProjectileSystem->getEntities();
	//std::cout << projectiles->size() << std::endl;
	//Entity* projectile = new Entity("Projectile");
	//projectiles->push_back(projectile);

	
	if (CollisionSystem->Active()) { CollisionSystem->Update(); }
	if (MovementSystem->Active()) { MovementSystem->Update(); }
	if (ControlSystem->Active()) 
	{ 
		ControlSystem->Update(); 
		ControlSystem->getSystemEntities(projectiles);
	}
	if (RenderSystem->Active()) { RenderSystem->Update(); }
	if (ProjectileSystem->Active()) { ProjectileSystem->Update(); }
}