#define SDL_MAIN_HANDLED
#include "ResourceManager.h"
#include "Entity.h"
#include "EventListener.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "MovementSystem.h"
#include "ProjectileSystem.h"
#include "ProjectileComponent.h"
#include "CollisionComponent.h"
#include "CollisionSystem.h"

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
	player->AddComponent(new PositionComponent(SDL_Point{300, 300}));
	player->AddComponent(new MovementComponent(3));
	player->AddComponent(new CollisionComponent());






	Entity * projectile = new Entity("Projectile");
	projectile->AddComponent(new SpriteComponent("Demon", 0, 0, 0, 16, 16, 0));
	projectile->AddComponent(new PositionComponent(SDL_Point{ 300, 300 } ));
	projectile->AddComponent(new ProjectileComponent(2, "Enemy", 5.0f, 3.0f, 10.0f));
	projectile->AddComponent(new MovementComponent());
	projectile->AddComponent(new CollisionComponent());



	Entity * projectile2 = new Entity("Projectile");
	projectile2->AddComponent(new SpriteComponent("Demon", 0, 0, 0, 16, 16, 0));
	projectile2->AddComponent(new PositionComponent(SDL_Point{ 300, 300 }));
	projectile2->AddComponent(new ProjectileComponent(3, "Enemy", 5.0f, 2.0f, 15.0f));
	projectile2->AddComponent(new MovementComponent());
	projectile2->AddComponent(new CollisionComponent());


	RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);
	r->AddEntity(player);
	r->AddEntity(projectile);
	r->AddEntity(projectile2);

	ProjectileSystem * p = new ProjectileSystem();
	p->AddEntity(projectile);
	p->AddEntity(projectile2);
	p->AddEntity(player);

	
	CollisionSystem * collision = new CollisionSystem();
	collision->AddEntity(player);
	collision->AddEntity(projectile);
	collision->AddEntity(projectile2);


	ControlSystem *c = new ControlSystem(listener);
	c->AddEntity(player);

	MovementSystem *m = new MovementSystem();
	m->AddEntity(player);
	m->AddEntity(projectile);
	m->AddEntity(projectile2);



	while (1 != 0)
	{
		SDL_PollEvent(e);

		input->handleInput(*e);

		c->Update();
		m->Update();
		p->Update();
		collision->Update();

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