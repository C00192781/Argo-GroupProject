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

	Entity * player = new Entity("Player");
	player->AddComponent(new SpriteComponent("Demon", 0, 0, 0, 16, 16, 0));
	player->AddComponent(new PositionComponent());
	AttributesComponent * test = new AttributesComponent();
	player->AddComponent(test);

	RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);
	r->AddEntity(player);

	HealthSystem * h = new HealthSystem();
	h->AddEntity(player);

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
		Modifer test = Modifer();
		test.type = ModiferTypes::DAMAGE;
		test.amount = 10;
		test.duration = 3;
		modifiers->push_back(test);
	}
	//player->AddComponent(new )

	while (1 != 0)
	{
		SDL_SetRenderDrawColor(gameRenderer, 100, 100, 0, 0);
		SDL_RenderClear(gameRenderer);
		r->Update();
		h->Update();

		AttributesComponent* component = static_cast<AttributesComponent*>((player)->GetComponents()->at(acKey));

		std::cout << component->Armour() << std::endl;
		std::cout << "TEST" << test->Armour() << std::endl;
		SDL_RenderPresent(gameRenderer);
	}
	return 0;
}