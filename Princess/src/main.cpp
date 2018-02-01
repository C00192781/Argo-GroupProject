#define SDL_MAIN_HANDLED
#include "ResourceManager.h"
#include "Entity.h"
#include "EventListener.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "ControlSystem.h"

int main()
{
	SDL_Window* gameWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	ResourceManager *resourceManager = new ResourceManager(gameRenderer, "Resources");
	resourceManager->AddTexture("Demon", "demon.png");

	EventListener *listener = new EventListener();

	InputHandler *input = new InputHandler(listener);

	Entity * player = new Entity("Player");
	player->AddComponent(new SpriteComponent("Demon", 0, 0, 0, 16, 16, 0));
	player->AddComponent(new PositionComponent(SDL_Point{100, 300}));
	player->AddComponent(new MovementComponent(3));

	RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);
	r->AddEntity(player);

	ControlSystem *c = new ControlSystem(listener);
	c->AddEntity(player);

	while (1 != 0)
	{
		SDL_PollEvent(e);

		input->handleInput(*e);

		c->Update();

		SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 0);
		SDL_RenderClear(gameRenderer);
		r->Update();
		SDL_RenderPresent(gameRenderer);
	}

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	IMG_Quit();
	SDL_Quit();

	return 0;
}