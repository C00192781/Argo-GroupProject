#define SDL_MAIN_HANDLED
#include "ResourceManager.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "AttributesComponent.h"
#include "HealthSystem.h"
#include <iostream>


int main()
{
	SDL_Window* gameWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	ResourceManager *resourceManager = new ResourceManager(gameRenderer, "Resources");
	resourceManager->AddTexture("Demon", "demon.png");
	resourceManager->AddTexture("Hearts", "hearts2.png");
	resourceManager->AddTexture("HeartsHealth", "heartsfull2.png");

	Entity * hearts = new Entity("Hearts");
	hearts->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>((hearts)->GetComponents()->at(0))->X(50);
	static_cast<PositionComponent*>((hearts)->GetComponents()->at(0))->Y(50);
	hearts->AddComponent(new SpriteComponent("Hearts", 0, 0, 0, 80, 16, 0));


	Entity * heartsHealth = new Entity("HeartsHealth");
	heartsHealth->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>((heartsHealth)->GetComponents()->at(0))->X(50);
	static_cast<PositionComponent*>((heartsHealth)->GetComponents()->at(0))->Y(50);
	heartsHealth->AddComponent(new SpriteComponent("HeartsHealth", 0, 0, 0, 80, 16, 0));

	Entity * player = new Entity("Player");
	player->AddComponent(new SpriteComponent("Demon", 0, 0, 0, 16, 16, 0));
	player->AddComponent(new PositionComponent());
	player->AddComponent(new AttributesComponent());

	RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);
	r->AddEntity(player);
	r->AddEntity(hearts);
	r->AddEntity(heartsHealth);

	HealthSystem * h = new HealthSystem();
	h->AddEntity(player);
	h->AddEntity(heartsHealth);

	int acKey = -1;
	for (int i = 0; i < player->GetComponents()->size(); i++)
	{
		if (player->GetComponents()->at(i)->Type() == "AC")
		{
			acKey = i;
		}
	}
	if (acKey >= 0)
	{
		std::list<Modifer> * modifiers = static_cast<AttributesComponent*>((player)->GetComponents()->at(acKey))->Modifers();
		modifiers->push_back(Modifer(ModiferTypes::DAMAGE, 115, 0));
	}


	while (1 != 0)
	{
		SDL_SetRenderDrawColor(gameRenderer, 100, 100, 0, 0);
		SDL_RenderClear(gameRenderer);
		r->Update();
		h->Update();

		AttributesComponent* component = static_cast<AttributesComponent*>((player)->GetComponents()->at(acKey));

		std::cout << component->Armour() << " " << component->Health() << std::endl;
		SDL_RenderPresent(gameRenderer);
	}
	return 0;
}