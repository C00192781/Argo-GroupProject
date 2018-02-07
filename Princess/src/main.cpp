#define SDL_MAIN_HANDLED

#include <iostream>
#include <time.h>
#include "Quad.h"
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
#include "AIsystem.h"
#include "Princess.h"
#include <chrono>

#include "SystemManager.h"

int main()
{


	SDL_Window* gameWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 816, 624, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();
	unsigned int lastTime = 0;
	float deltaTime = 0;
	unsigned int currentTime = 0;
	srand(time(NULL));

	bool debug = false;

	ResourceManager *resourceManager = new ResourceManager(gameRenderer, "Resources");

	resourceManager->AddTexture("Red", "Sprite_Red.png");
	resourceManager->AddTexture("Demon", "demon.png");
	resourceManager->AddTexture("Turf", "Turfs.png");

	EventListener *listener = new EventListener();

	InputHandler *input = new InputHandler(listener);

	StateManager state;

	SystemManager systemManager;
	systemManager.ControlSystem = new ControlSystem(listener);
	systemManager.ControlSystem->Active(true);
	systemManager.MovementSystem = new MovementSystem();
	systemManager.MovementSystem->Active(true);
	systemManager.RenderSystem = new RenderSystem(resourceManager, gameRenderer);
	systemManager.RenderSystem->Active(true);
	systemManager.RenderSystem->SetScale(3);
	systemManager.AttackSystem = new AttackSystem();
	systemManager.AttackSystem->Active(true);
	systemManager.AiSystems = new AiSystem();
	systemManager.AiSystems->Active(true);
	systemManager.CollisionSystem = new CollisionSystem(SDL_Rect{ 0, 0, SDL_GetWindowSurface(gameWindow)->w, SDL_GetWindowSurface(gameWindow)->h });
	//systemManager.CollisionSystem->Active(true);

	BattleMap map1 = BattleMap(&systemManager, gameRenderer, &state);
	map1.Generate("Grassland");

	Entity * player = new Entity("Player");
	player->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
	player->AddComponent(new PositionComponent(SDL_Point{100, 300}));
	player->AddComponent(new AttributesComponent());
	player->AddComponent(new MovementComponent(100));
	player->AddComponent(new CollisionComponent());
	player->AddComponent(new WeaponComponent(WeaponType::MELEE));

	//RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);
	///r->AddEntity(play//er);

	systemManager.ControlSystem->AddEntity(player);
	systemManager.MovementSystem->AddEntity(player);
	systemManager.RenderSystem->AddEntity(player);
	systemManager.AttackSystem->AddEntity(player);
	systemManager.CollisionSystem->AddEntity(player);
	//RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);

	bool heartTest = true;
	//princess->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	////Entity *meleeEnemy = new Entity("Melee Enemy");
	////meleeEnemy->AddComponent(new SpriteComponent("Demon", 0, 0, 0, 0, 16, 16, 0));
	////meleeEnemy->AddComponent(new PositionComponent(SDL_Point{ 550,500 }));
	////meleeEnemy->AddComponent(new MovementComponent(120));
	////meleeEnemy->AddComponent(new SeekComponent(600, 600));
	////meleeEnemy->AddComponent(new AttackComponent(1, 1, 1));

	////systemManager.AiSystems->AddEntity(meleeEnemy);
	////systemManager.RenderSystem->AddEntity(meleeEnemy);
	////systemManager.MovementSystem->AddEntity(meleeEnemy);

	while (1 != 0)
	{
		currentTime = SDL_GetTicks();
		SDL_PollEvent(e);
		if (currentTime > lastTime)
		{
			deltaTime = ((float)(currentTime - lastTime)) / 1000;

			input->handleInput(*e);

			lastTime = currentTime;
		}

		map1.Update();

		SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 0);
		SDL_RenderClear(gameRenderer);

		systemManager.Update(deltaTime);

		SDL_RenderPresent(gameRenderer);
	}

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	IMG_Quit();
	SDL_Quit();

	return 0;
}