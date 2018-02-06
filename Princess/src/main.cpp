#define SDL_MAIN_HANDLED

#include <iostream>
#include <time.h>

#include "ResourceManager.h"
#include "Entity.h"
#include "EventListener.h"
#include "BattleMap.h"
#include "StateManager.h"
#include "RectangleComponent.h"
#include "SpriteComponent.h"
#include "ProjectileSystem.h"
#include "ProjectileComponent.h"
#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "AttributesComponent.h"
#include "HealthSystem.h"
#include "HeartComponent.h"

#include "SystemManager.h"

int main()
{
	SDL_Window* gameWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 816, 624, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	srand(time(NULL));

	ResourceManager *resourceManager = new ResourceManager(gameRenderer, "Resources");

	resourceManager->AddTexture("Red", "Sprite_Red.png");
	resourceManager->AddTexture("Demon", "demon.png");
	resourceManager->AddTexture("Turf", "Turfs.png");

	EventListener *listener = new EventListener();

	InputHandler *input = new InputHandler(listener);

	StateManager state;
	
	std::vector<Entity*>* projectiles = new std::vector<Entity*>();


	SystemManager systemManager;
	systemManager.ControlSystem = new ControlSystem(listener);
	systemManager.ControlSystem->Active(true);
	systemManager.MovementSystem = new MovementSystem();
	systemManager.MovementSystem->Active(true);
	systemManager.RenderSystem = new RenderSystem(resourceManager, gameRenderer);
	systemManager.RenderSystem->Active(true);
	systemManager.RenderSystem->SetScale(3);
	systemManager.ProjectileSystem = new ProjectileSystem();
	systemManager.ProjectileSystem->Active(true);
	systemManager.CollisionSystem = new CollisionSystem(SDL_Rect{ 816, 624 });
	systemManager.CollisionSystem->Active(true);

	BattleMap map1 = BattleMap(&systemManager, gameRenderer, &state);
	map1.Generate("Grassland");

	Entity * player = new Entity("Player");
	player->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
	player->AddComponent(new RectangleComponent(SDL_Point{100, 300}, 16 * 3, 16 * 3));
	player->AddComponent(new AttributesComponent());
	player->AddComponent(new MovementComponent(3));
	player->AddComponent(new CollisionComponent());
	//RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);
	//r->AddEntity(player);

	systemManager.ControlSystem->AddEntity(player);
	systemManager.MovementSystem->AddEntity(player);
	systemManager.RenderSystem->AddEntity(player);
	//systemManager.ProjectileSystem->AddEntity(player);
	systemManager.CollisionSystem->AddEntity(player);

	//for (int i = 0; i < 200; i++)
	//{
	//	Entity* temp = new Entity("temp");
	//	temp->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
	//	temp->AddComponent(new RectangleComponent(SDL_Point{ 100, 300 }, 16 * 3, 16 * 3));
	//	temp->AddComponent(new MovementComponent(3));
	//	temp->AddComponent(new CollisionComponent());
	//
	//	//systemManager.ControlSystem->AddEntity(player);
	//	systemManager.MovementSystem->AddEntity(player);
	//	systemManager.RenderSystem->AddEntity(player);
	//	//systemManager.ProjectileSystem->AddEntity(player);
	//	systemManager.CollisionSystem->AddEntity(player);
	//}

	bool heartTest = true;

	while (1 != 0)
	{
		input->handleInput(*e);

		map1.Update();

		SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 0);
		SDL_RenderClear(gameRenderer);

		systemManager.Update();

		SDL_RenderPresent(gameRenderer);
	}

	SDL_RenderPresent(gameRenderer);

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	IMG_Quit();
	SDL_Quit();

	return 0;
}