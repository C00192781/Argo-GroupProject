#include "SystemManager.h"

SystemManager::SystemManager(ResourceManager *resourceManager, SDL_Renderer* gameRenderer, EventListener *listener, std::vector<Entity*>* projectiles, AStar* aStar, StateManager &state)
{
	networkSystem = new NetworkSystem(listener);

	controlSystem = new ControlSystem(listener);
	controlSystem->Active(true);

	movementSystem = new MovementSystem(816, 624, listener);
	movementSystem->Active(true);

	renderSystem = new RenderSystem(resourceManager, gameRenderer);
	renderSystem->Active(true);
	renderSystem->SetScale(3);
	renderSystem->Camera(true);
	renderSystem->Camera(816, 624);

	textRenderSystem = new TextRenderSystem(resourceManager, gameRenderer);
	textRenderSystem->Active(true);

	attackSystem = new AttackSystem(projectiles);
	attackSystem->Active(true);

	collisionSystem = new CollisionSystem(listener);
	collisionSystem->Active(true);

	aiSystem = new AiSystem(aStar);
	aiSystem->Active(true);

	healthSystem = new HealthSystem(&state);
	healthSystem->Active(true);

	buttonSystem = new ButtonSystem(listener);
	buttonSystem->Active(true);

	soundSystem = new SoundSystem(resourceManager);
	soundSystem->Active(true);

	mementoSystem = new MementoCaretaker(&state);
	mementoSystem->Active(true);
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

	if (networkSystem->Active()) { networkSystem->Update(deltaTime); }

	//if (soundSystem->Active()) { soundSystem->Update(); }

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
	networkSystem->SelectiveClear();
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
	networkSystem->FullClear();
	mementoSystem->FullClear();
}