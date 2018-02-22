#include "SystemManager.h"

SystemManager::SystemManager(ResourceManager *resourceManager, SDL_Renderer* gameRenderer, EventListener *listener, std::vector<Entity*>* projectiles)
{

}

void SystemManager::Update(float deltaTime, std::vector<Entity*> players)
{
	if (controlSystem->Active()) { controlSystem->Update(); }

	if (attackSystem->Active()) { attackSystem->Update(deltaTime); }

	if (aiSystem->Active()) { aiSystem->Update(deltaTime, players); }

	if (collisionSystem->Active()) { collisionSystem->Update(); }

	if (movementSystem->Active()) { movementSystem->Update(deltaTime); }

	if (buttonSystem->Active()) { buttonSystem->Update(); }

	if (textRenderSystem->Active()) { textRenderSystem->Update(); }

	if (healthSystem->Active()) { healthSystem->Update(deltaTime); }

	if (soundSystem->Active()) { soundSystem->Update(); }

	if (renderSystem->Active()) { renderSystem->Update(); }

	if (menuSystem->Active()) { menuSystem->Update(); }

	if (mementoSystem->Active()) { mementoSystem->Update(); }
}

