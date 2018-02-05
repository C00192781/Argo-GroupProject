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
#include "AIsystem.h"
#include "Princess.h"


#include "SystemManager.h"

int main()
{
	SDL_Window* gameWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 816, 624, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	srand(time(NULL));

	bool debug = false;

	ResourceManager *resourceManager = new ResourceManager(gameRenderer, "Resources");
	resourceManager->AddTexture("Demon", "demon.png");
	resourceManager->AddTexture("Turf", "Turfs.png");
	resourceManager->AddTexture("Hearts", "hearts2.png");
	resourceManager->AddTexture("HeartsHealth", "heartsfull2.png");
	resourceManager->AddTexture("HeartsSheet", "heartSpriteSheet.png");
	resourceManager->AddTexture("ArmourSheet", "armourSpriteSheet.png");

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
	systemManager.AiSystem = new AiSystem();
	systemManager.AiSystem->Active(true);

	/*for (auto i = systemManager.AiSystem->getEntities(), e = systemManager.AiSystem->getEntities(); i != e; i++)
	{
		systemManager.RenderSystem->AddEntity(systemManager.AiSystem->getEntities());
	}
	*/
	



	BattleMap map1 = BattleMap(&systemManager, gameRenderer, &state);
	map1.Generate("Grassland");




	while (1 != 0)
	{
		SDL_PollEvent(e);

		input->handleInput(*e);

		map1.Update();
		//c->Update();
		//m->Update();
		//p->Update();
		//collision->Update();

		SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 0);
		SDL_RenderClear(gameRenderer);

		systemManager.Update();

		if (debug == false)
		{
			auto mrEntity = systemManager.AiSystem->getEntities();
			systemManager.RenderSystem->AddEntity(mrEntity.at(0));
			debug = true;
		}

		SDL_RenderPresent(gameRenderer);
	
		
	}


	SDL_RenderPresent(gameRenderer);

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	IMG_Quit();
	SDL_Quit();

	return 0;
}