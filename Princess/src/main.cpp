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

#include "SystemManager.h"

int main()
{
	SDL_Window* gameWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 816, 624, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	srand(time(NULL));

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

	BattleMap map1 = BattleMap(&systemManager, gameRenderer, &state);
	map1.Generate("Grassland");

	//Entity * player = new Entity("Player");
	//player->AddComponent(new SpriteComponent("Demon", 1, 0, 0, 0, 16, 16, 0));
	//player->AddComponent(new PositionComponent(SDL_Point{ 300, 300 }));
	//player->AddComponent(new AttributesComponent());
	//player->AddComponent(new MovementComponent(3));
	//player->AddComponent(new CollisionComponent());
	//int heartNum = (static_cast<AttributesComponent*>((player)->GetComponents()->at(2))->MaxHealth()) / 2;
	//int armourNum = (static_cast<AttributesComponent*>((player)->GetComponents()->at(2))->MaxArmour()) / 2;
	//
	//
	//Entity * projectile = new Entity("Projectile");
	//projectile->AddComponent(new SpriteComponent("Demon", 1, 0, 0, 0, 16, 16, 0));
	//projectile->AddComponent(new PositionComponent(SDL_Point{ 300, 300 } ));
	//projectile->AddComponent(new ProjectileComponent(2, "Enemy", 5.0f, 3.0f, 10.0f));
	//projectile->AddComponent(new MovementComponent());
	//projectile->AddComponent(new CollisionComponent());
	//
	//
	//
	//Entity * projectile2 = new Entity("Projectile");
	//projectile2->AddComponent(new SpriteComponent("Demon", 1, 0, 0, 0, 16, 16, 0));
	//projectile2->AddComponent(new PositionComponent(SDL_Point{ 300, 300 }));
	//projectile2->AddComponent(new ProjectileComponent(3, "Enemy", 5.0f, 2.0f, 15.0f));
	//projectile2->AddComponent(new MovementComponent());
	//projectile2->AddComponent(new CollisionComponent());
	//
	//std::vector<Entity*>* hearts = new std::vector<Entity*>();
	//for (int i = 0; i < heartNum; i++)
	//{
	//	Entity * heart = new Entity("Hearts");
	//	heart->AddComponent(new PositionComponent());
	//
	//	if (i >= 10)
	//	{
	//		static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->setX(20 * (i-10));
	//		static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->setY(20+20);
	//	}
	//	else
	//	{
	//		static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->setX(20 * i);
	//		static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->setY(20);
	//	}
	//	heart->AddComponent(new SpriteComponent("HeartsSheet", 2, 3, 0, 0, 16, 16, 0));
	//	heart->AddComponent(new HeartComponent(hearts));
	//	hearts->push_back(heart);
	//	static_cast<HeartComponent*>((heart)->GetComponents()->at(2))->Index(hearts->size() - 1);
	//}
	//
	//std::vector<Entity*>* armourDisplayVector = new std::vector<Entity*>();
	//for (int i = 0; i < armourNum; i++)
	//{
	//	Entity * armour = new Entity("ArmourDisplay");
	//	armour->AddComponent(new PositionComponent());
	//
	//	if (i >= 10)
	//	{
	//		static_cast<PositionComponent*>((armour)->GetComponents()->at(0))->setX(20 * (i - 10));
	//		static_cast<PositionComponent*>((armour)->GetComponents()->at(0))->setY(60 + 20);
	//	}
	//	else
	//	{
	//		static_cast<PositionComponent*>((armour)->GetComponents()->at(0))->setX(20 * i);
	//		static_cast<PositionComponent*>((armour)->GetComponents()->at(0))->setY(60);
	//	}
	//	armour->AddComponent(new SpriteComponent("ArmourSheet", 2, 3, 0, 0, 16, 16, 0));
	//	armour->AddComponent(new HeartComponent(armourDisplayVector));
	//	static_cast<HeartComponent*>((armour)->GetComponents()->at(2))->HeartType(HeartTypes::ARMOUR);
	//	armourDisplayVector->push_back(armour);
	//	static_cast<HeartComponent*>((armour)->GetComponents()->at(2))->Index(armourDisplayVector->size() - 1);
	//}
	//
	//
	//
	//RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);
	//r->AddEntity(player);
	//r->AddEntity(projectile);
	//r->AddEntity(projectile2);
	//
	//ProjectileSystem * p = new ProjectileSystem();
	//p->AddEntity(projectile);
	//p->AddEntity(projectile2);
	//p->AddEntity(player);
	//
	//
	//CollisionSystem * collision = new CollisionSystem();
	//collision->AddEntity(player);
	//collision->AddEntity(projectile);
	//collision->AddEntity(projectile2);
	//
	//for (int i = 0; i < hearts->size(); i++)
	//{
	//	r->AddEntity(hearts->at(i));
	//}
	//for (int i = 0; i < armourDisplayVector->size(); i++)
	//{
	//	r->AddEntity(armourDisplayVector->at(i));
	//}
	//
	//HealthSystem * h = new HealthSystem();
	//h->AddEntity(player);
	//for (int i = 0; i < hearts->size(); i++)
	//{
	//	h->AddEntity(hearts->at(i));
	//}
	//for (int i = 0; i < armourDisplayVector->size(); i++)
	//{
	//	h->AddEntity(armourDisplayVector->at(i));
	//}
	//
	//int acKey = -1;
	//for (int i = 0; i < player->GetComponents()->size(); i++)
	//{
	//	if (player->GetComponents()->at(i)->Type() == "AC")
	//	{
	//		acKey = i;
	//	}
	//}
	//if (acKey >= 0)
	//{
	//	std::list<Modifer> * modifiers = static_cast<AttributesComponent*>((player)->GetComponents()->at(acKey))->Modifers();
	//}

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

		SDL_RenderPresent(gameRenderer);
	
		//h->Update();
		//if (heartTest == true)
		//{
		//	AttributesComponent* component = static_cast<AttributesComponent*>((player)->GetComponents()->at(acKey));
		//	//Health
		//	component->MaxHealth(40);
		//	int size = hearts->size();
		//	h->UpdateMaxHearts();
		//	if (size < hearts->size())
		//	{
		//		for (int i = size; i < hearts->size(); i++)
		//		{
		//			r->AddEntity(hearts->at(i));
		//			h->AddEntity(hearts->at(i));
		//		}
		//	}
		//	h->UpdateHeartsStatus(player);
		//
		//	//Armour
		//	component->MaxArmour(8);
		//	size = armourDisplayVector->size();
		//	h->UpdateMaxArmour();
		//	if (size < armourDisplayVector->size())
		//	{
		//		for (int i = size; i < armourDisplayVector->size(); i++)
		//		{
		//			r->AddEntity(armourDisplayVector->at(i));
		//			h->AddEntity(armourDisplayVector->at(i));
		//		}
		//	}
		//	h->UpdateArmourStatus(player);
		//
		//	heartTest = false;
		//
		//}
	}

	//hearts->clear();
	//hearts->shrink_to_fit();
	//
	//armourDisplayVector->clear();
	//armourDisplayVector->shrink_to_fit();

	SDL_RenderPresent(gameRenderer);

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	IMG_Quit();
	SDL_Quit();

	return 0;
}