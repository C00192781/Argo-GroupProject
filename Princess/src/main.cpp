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
#include "AISystem.h"
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

	srand(time(NULL));

	ResourceManager *resourceManager = new ResourceManager(gameRenderer, "Resources");

	resourceManager->AddTexture("Red", "Sprite_Red.png");
	resourceManager->AddTexture("Demon", "demon.png");
	resourceManager->AddTexture("Turf", "Turfs.png");
	resourceManager->AddTexture("Arrow", "Arrow.png");
	resourceManager->AddTexture("HeartsSheet", "heartSpriteSheet.png");
	resourceManager->AddTexture("ArmourSheet", "armourSpriteSheet.png");

	EventListener *listener = new EventListener();

	InputHandler *input = new InputHandler(listener);

	StateManager state;
	
	std::vector<Entity*>* projectiles = new std::vector<Entity*>;

	SystemManager systemManager(resourceManager, gameRenderer, listener, projectiles);

	BattleMap map1 = BattleMap(&systemManager, gameRenderer, &state);
	map1.Generate("Grassland");

	bool heartTest = true;

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

	SDL_RenderPresent(gameRenderer);

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	IMG_Quit();
	SDL_Quit();

	return 0;
}