#include "SystemManager.h"

SystemManager::SystemManager(ResourceManager *resourceManager, SDL_Renderer* gameRenderer, EventListener *listener, std::vector<Entity*>* projectiles, StateManager* state)
{
	controlSystem = new ControlSystem(listener);
	controlSystem->Active(true);

	movementSystem = new MovementSystem(816, 624);
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

	aiSystem = new AiSystem();
	aiSystem->Active(true);

	healthSystem = new HealthSystem();
	healthSystem->Active(true);

	menuSystem = new MenuSystem(listener, state);
	menuSystem->Active(true);

	buttonSystem = new ButtonSystem(listener);
	buttonSystem->Active(true);

	soundSystem = new SoundSystem(resourceManager);
	soundSystem->Active(true);
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

	if (menuSystem->Active()) { menuSystem->Update(); }

	if (soundSystem->Active()) { soundSystem->Update(); }

	if (renderSystem->Active()) { renderSystem->Update(); }

	if (textRenderSystem->Active()) { textRenderSystem->Update(); }
}

