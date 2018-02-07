#define SDL_MAIN_HANDLED

#include <iostream>
#include <time.h>

#include "ResourceManager.h"
#include "Entity.h"
#include "EventListener.h"
#include "BattleMap.h"
#include "StateManager.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "ProjectileSystem.h"
#include "ProjectileComponent.h"
#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "AttributesComponent.h"
#include "HealthSystem.h"
#include "HeartComponent.h"
#include "WorldMap.h"

#include "Quad.h"

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
	resourceManager->AddTexture("WorldTurf", "World_Turfs.png");

	EventListener *listener = new EventListener();

	InputHandler *input = new InputHandler(listener, e);

	StateManager state;

	Quad quado = Quad(816, 624, 2);

	SystemManager systemManager;
	systemManager.ControlSystem = new ControlSystem(listener, input);
	systemManager.ControlSystem->Active(true);
	systemManager.MovementSystem = new MovementSystem();
	systemManager.MovementSystem->Active(true);
	systemManager.RenderSystem = new RenderSystem(resourceManager, gameRenderer);
	systemManager.RenderSystem->Active(true);
	systemManager.RenderSystem->SetScale(1);

	//BattleMap battleMap = BattleMap(&systemManager, &state);
	//battleMap.Generate("Grassland");

	WorldMap* m = new WorldMap(&systemManager, &state);
	m->Generate(25, 25, 100);

	std::vector<Entity*> entitys;

	for (int i = 0; i < 5000; i++)
	{
		Entity * player = new Entity("Player");
		player->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
		player->AddComponent(new PositionComponent(SDL_Point{ rand() % 600, rand() % 600 }));
		player->AddComponent(new AttributesComponent());
		player->AddComponent(new MovementComponent(3));
		player->AddComponent(new CollisionComponent());
		RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);
		r->AddEntity(player);
		entitys.push_back(player);
		systemManager.ControlSystem->AddEntity(player);
		systemManager.MovementSystem->AddEntity(player);
		systemManager.RenderSystem->AddEntity(player);
	}

	bool heartTest = true;
	

	while (1 != 0)
	{
		input->handleInput();

		m->Update();
		quado.Fission(&entitys);

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