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
	systemManager.AiSystems = new AiSystem();
	systemManager.AiSystems->Active(true);
	

	BattleMap map1 = BattleMap(&systemManager, gameRenderer, &state);
	map1.Generate("Grassland");

	RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);

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


	Quadtree* quad = new Quadtree(0, SDL_Rect{1,1  , 816, 624 });
	
	std::vector<Entity*> mommy;

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
		auto daddy = systemManager.AiSystems->getEntities();

		quad->clear();
		quad->init();
		for (int i = 0; i < daddy.size(); i++) 
		{
			quad->insert(daddy.at(i));
		}


		std::vector<Entity*> entityVec;

		//entityVec.reserve(daddy.size());

		for (int i = 0; i < daddy.size(); i++)
		{
			entityVec.clear();
			entityVec = quad->retrieve(entityVec, daddy.at(i));

		//	auto mommwhy = quad->retrieve(entityVec, daddy.at(i));
			  //auto something =
			 if (entityVec.size() > 0)
			 { 
			//	 cout << "FREDIERCUS REX UNSER KONIG UND HERR" << endl;
			 }
			 else if (entityVec.size() == 0)
			 {
				 cout << "eine jede kugel die trifft ja nicht" << endl;
			 }
			// mommy.insert(mommy.end(), something.begin(), something.end());
			 
		//	 mommy.insert()

	//		 older.insert(holder.end(), backgroundHolder.begin(), backgroundHolder.end());

			//entityVec.insert(mommy)'
			 int q = 5;
			 q -= 5;
		}
	//	entityVec = mommy;

		for (int x = 0; x < entityVec.size(); x++)
		{
			//cout << entityVec.size() << endl;
			/*auto temp = entityVec;

			int q = 5;
			q -= 5;
*/
			auto temp1 = entityVec.at(0);
		//	static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().y
			auto rect1 = static_cast<SpriteComponent*>(temp1->GetComponents()->at(1))->GetRect();

			auto temp2 = entityVec.at(1);
			//	static_cast<PositionComponent*>(entity->GetComponents()->at(2))->getPosition().y
			auto rect2 = static_cast<SpriteComponent*>(temp1->GetComponents()->at(1))->GetRect();

			rect1.x += static_cast<PositionComponent*>(temp1->GetComponents()->at(2))->getPosition().x;
			rect1.x += static_cast<PositionComponent*>(temp1->GetComponents()->at(2))->getPosition().y;

			rect2.x += static_cast<PositionComponent*>(temp2->GetComponents()->at(2))->getPosition().x;
			rect2.x += static_cast<PositionComponent*>(temp2->GetComponents()->at(2))->getPosition().y;

			if (SDL_HasIntersection(&rect1, &rect2))
			{
			//	cout << "hit " << endl;
			}

			if (!SDL_HasIntersection(&rect1, &rect2))
			{
			//	cout << "miss " << endl;
			}
			//collision detection
		}

		//List returnObjects = new ArrayList();
		//for (int i = 0; i < allObjects.size(); i++) {
		//	returnObjects.clear();
		//	quad.retrieve(returnObjects, objects.get(i));

		//	for (int x = 0; x < returnObjects.size(); x++) {
		//		// Run collision detection algorithm between objects
		//	}

		input->handleInput(*e);

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