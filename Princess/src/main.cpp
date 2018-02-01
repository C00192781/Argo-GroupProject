#define SDL_MAIN_HANDLED
#include "ResourceManager.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "ProjectileSystem.h"

int main()
{
	SDL_Window* gameWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	ResourceManager *resourceManager = new ResourceManager(gameRenderer, "Resources");
	resourceManager->AddTexture("Demon", "demon.png");

	Entity * player = new Entity("Player");
	player->AddComponent(new SpriteComponent("Demon", 0, 0, 0, 16, 16, 0));

	PositionComponent playerPosition;
	player->AddComponent(&playerPosition);

	// EXAMPLE PROJECTILE ENTITY
	Entity * projectile = new Entity("Projectile");
	projectile->AddComponent(new SpriteComponent("Demon", 0, 0, 0, 16, 16, 0));

	PositionComponent projectilePosition;
	projectile->AddComponent(&projectilePosition);

	RenderSystem * r = new RenderSystem(resourceManager, gameRenderer);
	r->AddEntity(player);
	r->AddEntity(projectile);

	ProjectileSystem * p = new ProjectileSystem(500, 300, 8, 0.8);
	p->AddEntity(projectile);

	while (1 != 0)
	{
		SDL_SetRenderDrawColor(gameRenderer, 100, 100, 0, 0);
		SDL_RenderClear(gameRenderer);
		r->Update();
		p->Update();
		SDL_RenderPresent(gameRenderer);
	}
	return 0;
}