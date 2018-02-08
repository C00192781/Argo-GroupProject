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
#include "LTimer.h"
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
	const int SCREEN_FPS = 600;
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

	EventListener *listener = new EventListener();

	InputHandler *input = new InputHandler(listener);

	StateManager state;

	std::vector<Entity*>* projectiles = new std::vector<Entity*>();

	//for (int i = 0; i < 50; i++)
	//{
	//	projectiles->push_back()
	//}


	SystemManager systemManager;
	systemManager.ControlSystem = new ControlSystem(listener);
	systemManager.ControlSystem->Active(true);
	systemManager.MovementSystem = new MovementSystem();
	systemManager.MovementSystem->Active(true);
	systemManager.RenderSystem = new RenderSystem(resourceManager, gameRenderer);
	systemManager.RenderSystem->Active(true);
	systemManager.RenderSystem->SetScale(3);
	systemManager.RenderSystem->Camera(true);
	systemManager.RenderSystem->Camera(816, 624);

	systemManager.ProjectileSystem = new ProjectileSystem();
	systemManager.ProjectileSystem->Active(true);
	systemManager.CollisionSystem = new CollisionSystem();
	systemManager.CollisionSystem->Active(true);
	
	systemManager.AiSystem = new AiSystem();
	systemManager.AiSystem->Active(true);

	systemManager.healthSystem = new HealthSystem();
	systemManager.healthSystem->Active(true);

	BattleMap m = BattleMap(&systemManager, &state);
	m.Generate("Grassland");

	///*Entity * player = new Entity("Player");
	//player->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
	//player->Transient(true);
	//player->AddComponent(new PositionComponent(SDL_Point{ 0, 0 }));
	//player->AddComponent(new AttributesComponent());
	//player->AddComponent(new MovementComponent(3));
	//player->AddComponent(new CollisionComponent());
	//player->Active(true);*/


	//Entity * player = new Entity("Player");
	//player->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
	//player->AddComponent(new PositionComponent(SDL_Point{100, 300}));
	//player->AddComponent(new AttributesComponent());
	//player->AddComponent(new MovementComponent(3));
	//player->AddComponent(new CollisionComponent());
	//player->AddComponent(new AttributesComponent());
	////RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);
	////r->AddEntity(player);

	//systemManager.ControlSystem->AddEntity(player);
	//systemManager.MovementSystem->AddEntity(player);
	//systemManager.RenderSystem->AddEntity(player);
	//systemManager.ProjectileSystem->AddEntity(player);
	//systemManager.CollisionSystem->AddEntity(player);
	//systemManager.healthSystem->AddEntity(player);

	bool heartTest = true;

	//RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);

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

	std::vector<Entity*> collVector;
	Quadtree* quad = new Quadtree(0, SDL_Rect{ 0,0  , 816, 624 });

	while (1 != 0)
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
			cout << "FPS (With Cap) " << avgFPS << endl;;
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
			SDL_PollEvent(e);
			if (currentTime > lastTime)
			{
				deltaTime = ((float)(currentTime - lastTime)) / 1000;

				input->handleInput(*e);

				lastTime = currentTime;
			}


			auto aiSystemEntities = systemManager.AiSystem->getEntities();

			quad->clear();
			quad->init();
			for (int i = 0; i < aiSystemEntities.size(); i++)
			{
				quad->insert(aiSystemEntities.at(i));
				
			}
			
////	/*		for (int i = 0; i < projectiles->size(); i++)
////			{
////				quad->insert(projectiles->at(i));
////			}
////*/
			//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

			std::vector<Entity*> entityVec;

			collVector.clear(); 
	

			for (int i = 0; i < aiSystemEntities.size(); i++)
			{

				collVector.push_back(aiSystemEntities.at(i));
			}

			for (int i = 0; i < collVector.size(); i++)
			{
				entityVec.clear();
				entityVec = quad->retrieve(entityVec, collVector.at(i));

				if (entityVec.size() > 0)
				{
					//	 cout << "FRIDERICUS REX UNSER KONIG UND HERR" << endl;
				}
				else if (entityVec.size() == 0)
				{
					cout << "quad empty" << endl;
				}
			}

			for (int x = 0; x < entityVec.size(); x++) //check collision between entities in the current (sub)quadrant
			{
				auto temp1 = entityVec.at(x);
				auto rect1 = static_cast<SpriteComponent*>(temp1->GetComponents()->at(1))->GetRect();

				rect1.x += static_cast<PositionComponent*>(temp1->GetComponents()->at(2))->getPosition().x;
				rect1.x += static_cast<PositionComponent*>(temp1->GetComponents()->at(2))->getPosition().y;

				for (int y = 0; y < entityVec.size(); y++)
				{
					if (x != y) //things don't collide with themselves
					{
						auto temp2 = entityVec.at(y);
						auto rect2 = static_cast<SpriteComponent*>(temp1->GetComponents()->at(1))->GetRect();
						rect2.x += static_cast<PositionComponent*>(temp2->GetComponents()->at(2))->getPosition().x;
						rect2.x += static_cast<PositionComponent*>(temp2->GetComponents()->at(2))->getPosition().y;

						if (SDL_HasIntersection(&rect1, &rect2))
						{
					//		cout << "hit " << endl;
						}

						if (!SDL_HasIntersection(&rect1, &rect2))
						{
							//	cout << "miss " << endl;
						}
					}
				}
			}
			//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

			input->handleInput(*e);
			m.Update();

			SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 0);
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