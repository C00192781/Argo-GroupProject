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

	if (healthSystem->Active()) { healthSystem->Update(deltaTime); }

	if (soundSystem->Active()) { soundSystem->Update(); }

	if (renderSystem->Active()) { renderSystem->Update(); }

	if (mementoSystem->Active()) { mementoSystem->Update(); }

	if (textRenderSystem->Active()) { textRenderSystem->Update(); }
}

void SystemManager::MassSelectiveClear()
{
	controlSystem->SelectiveClear();
	attackSystem->SelectiveClear();
	aiSystem->SelectiveClear();
	collisionSystem->SelectiveClear();
	movementSystem->SelectiveClear();
	buttonSystem->SelectiveClear();
	renderSystem->SelectiveClear();
	textRenderSystem->SelectiveClear();
	healthSystem->SelectiveClear();
	soundSystem->SelectiveClear();
	mementoSystem->SelectiveClear();
}

void SystemManager::MassClear()
{
	controlSystem->FullClear();
	attackSystem->FullClear();
	aiSystem->FullClear();
	collisionSystem->FullClear();
	movementSystem->FullClear();
	buttonSystem->FullClear();
	renderSystem->FullClear();
	textRenderSystem->FullClear();
	healthSystem->FullClear();
	soundSystem->FullClear();
	mementoSystem->FullClear();
}