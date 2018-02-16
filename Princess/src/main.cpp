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
#include "TextComponent.h"
#include "TextRenderSystem.h"
#include "ButtonComponent.h"
#include "HealthSystem.h"
#include "AISystem.h"
#include "Princess.h"
#include <chrono>
#include "SystemManager.h"
#include "LTimer.h"
#include "WorldMap.h"
#include "TownInstance.h"
#include "ShopInstance.h"

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

	const int SCREEN_FPS = 500;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };

	//The frames per second timer
	LTimer fpsTimer;

	//The frames per second cap timer
	LTimer capTimer;

	//In memory text stream
	std::stringstream timeText;

	//Start counting frames per second
	int countedFrames = 0;
	fpsTimer.start();

	ResourceManager *resourceManager = new ResourceManager(gameRenderer, "Resources");

	resourceManager->AddTexture("Red", "Sprite_Red.png");
	resourceManager->AddTexture("Demon", "demon.png");
	resourceManager->AddTexture("Turf", "Turfs.png");
	resourceManager->AddTexture("Arrow", "Arrow.png");
	resourceManager->AddTexture("HeartsSheet", "heartSpriteSheet.png");
	resourceManager->AddTexture("ArmourSheet", "armourSpriteSheet.png");
	resourceManager->AddTexture("WorldTurf", "World_Turfs.png");
	resourceManager->AddTexture("Button", "Button.png");
	resourceManager->AddTexture("Plate", "Plate.png");
	resourceManager->AddTexture("Heart", "Hearts.png");
	resourceManager->AddTexture("Armor", "Armors.png");

	resourceManager->AddFont("ComicSans", "ComicSans.ttf", 21);

	EventListener *listener = new EventListener();

	InputHandler *input = new InputHandler(listener, e);

	StateManager state;

	std::vector<Entity*>* projectiles = new std::vector<Entity*>;

	SystemManager systemManager(resourceManager, gameRenderer, listener, projectiles);

	systemManager.controlSystem = new ControlSystem(listener);
	systemManager.controlSystem->Active(true);

	systemManager.movementSystem = new MovementSystem();
	systemManager.movementSystem->Active(true);

	systemManager.renderSystem = new RenderSystem(resourceManager, gameRenderer);
	systemManager.renderSystem->Active(true);
	systemManager.renderSystem->SetScale(3);
	systemManager.renderSystem->Camera(true);
	systemManager.renderSystem->Camera(816, 624);

	systemManager.healthSystem = new HealthSystem();
	systemManager.healthSystem->Active(true);

	systemManager.textRenderSystem = new TextRenderSystem(resourceManager, gameRenderer);
	systemManager.textRenderSystem->Active(true);

	systemManager.attackSystem = new AttackSystem(projectiles);
	systemManager.attackSystem->Active(true);

	systemManager.projectileSystem = new ProjectileSystem();
	systemManager.projectileSystem->Active(true);

	systemManager.collisionSystem = new CollisionSystem();
	systemManager.collisionSystem->Active(true);

	systemManager.aiSystem = new AiSystem();
	systemManager.aiSystem->Active(true);

	systemManager.healthSystem = new HealthSystem();
	systemManager.healthSystem->Active(true);

	systemManager.buttonSystem = new ButtonSystem(listener);
	systemManager.buttonSystem->Active(true);

	for (int i = 0; i < 4; i++)
	{
		Entity * player = new Entity("Player");
		player->Active(true);
		player->AddComponent(new SpriteComponent("Red", 3, 1, 0, 0, 16, 16, 0));
		player->AddComponent(new PositionComponent(SDL_Point{ 0, 0 }));
		player->AddComponent(new AttributesComponent(21, 24, 9, 12, 100, 100));
		player->AddComponent(new MovementComponent());
		player->AddComponent(new WeaponComponent(WeaponType::RANGE));
		player->AddComponent(new CollisionComponent(100, 300, 16, 16, 2));
		player->Transient(true);

		for (int j = 0; j < 12; j++)
		{
			SpriteComponent * s = new SpriteComponent("Heart", 5, 0, 0, 0, 4, 4, 0);
			s->Relative(true);
			Entity * heart = new Entity("Heart");
			heart->AddComponent(new PositionComponent());
			heart->AddComponent(s);
			systemManager.healthSystem->AddEntity(heart, "PH" + std::to_string(i+1));
			systemManager.renderSystem->AddEntity(heart);
			heart->Transient(true);
		}
		for (int j = 0; j < 6; j++)
		{
			SpriteComponent * s = new SpriteComponent("Armor", 5, 0, 0, 0, 4, 4, 0);
			s->Relative(true);
			Entity * heart = new Entity("Heart");
			heart->AddComponent(new PositionComponent());
			heart->AddComponent(s);
			systemManager.healthSystem->AddEntity(heart, "PH" + std::to_string(i+1));
			systemManager.renderSystem->AddEntity(heart);
			heart->Transient(true);
		}
		systemManager.healthSystem->AddEntity(player, "");

		systemManager.controlSystem->AddEntity(player);
		systemManager.movementSystem->AddEntity(player);
		systemManager.renderSystem->AddEntity(player);
		systemManager.projectileSystem->AddEntity(player);
		systemManager.collisionSystem->AddEntity(player);
		systemManager.attackSystem->AddEntity(player);
	}

	BattleMap m = BattleMap(&systemManager, &state);
	m.Generate("jimmie");

	//TownInstance t = TownInstance(&systemManager);
	//t.Generate("jimmie");

	//WorldMap* m = new WorldMap(&systemManager, &state);
	//m->Generate(25, 25, 100);

	//ShopInstance s = ShopInstance(&systemManager);
	//s.Generate(1);

	while (true)
	{
		//Calculate and correct fps
		int avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		//Set text to be rendered
		if (avgFPS > 1)
		{
			//cout << "FPS (With Cap) " << avgFPS << endl;;
		}
		//update ren
		++countedFrames;

		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);

			currentTime = SDL_GetTicks();
			if (currentTime > lastTime)
			{
				deltaTime = ((float)(currentTime - lastTime)) / 1000;

				input->handleInput();

				lastTime = currentTime;
			}

			SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
			SDL_RenderClear(gameRenderer);

			systemManager.Update(deltaTime);

			SDL_RenderPresent(gameRenderer);
		}
	}

	SDL_RenderPresent(gameRenderer);

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	IMG_Quit();
	SDL_Quit();

	return 0;
}
