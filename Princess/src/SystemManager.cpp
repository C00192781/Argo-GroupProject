#include "SystemManager.h"

SystemManager::SystemManager(ResourceManager *resourceManager, SDL_Renderer* gameRenderer, EventListener *listener, std::vector<Entity*>* projectiles)
{

}

void SystemManager::Update(float deltaTime)
{
	if (controlSystem->Active()) { controlSystem->Update(); }
	if (attackSystem->Active()) { attackSystem->Update(deltaTime); }
	if (aiSystem->Active()) { aiSystem->Update(deltaTime); }
	if (collisionSystem->Active()) { collisionSystem->Update(); }
	if (movementSystem->Active()) { movementSystem->Update(deltaTime); }
	//if (buttonSystem->Active()) { buttonSystem->Update(); }
	if (renderSystem->Active()) { renderSystem->Update(); }
	//if (textRenderSystem->Active()) { textRenderSystem->Update(); }
}