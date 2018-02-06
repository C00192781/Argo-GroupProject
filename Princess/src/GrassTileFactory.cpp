#include "GrassTileFactory.h"

std::shared_ptr<Entity> GrassTileFactory::GroundA(std::string textureID, int x, int y)
{
	std::shared_ptr<Entity> holder = std::shared_ptr<Entity>(new Entity("Grass"));
	holder->AddComponent(std::shared_ptr<SpriteComponent>(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 0)));
	holder->AddComponent(std::shared_ptr<RectangleComponent>(new RectangleComponent()));
	std::static_pointer_cast<RectangleComponent>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	return holder;
}

std::shared_ptr<Entity> GrassTileFactory::GroundB(std::string textureID, int x, int y)
{
	std::shared_ptr<Entity> holder = std::shared_ptr<Entity>(new Entity("Dirt Holes"));
	holder->AddComponent(std::shared_ptr<SpriteComponent>(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 1)));
	holder->AddComponent(std::shared_ptr<RectangleComponent>(new RectangleComponent()));
	std::static_pointer_cast<RectangleComponent>(holder->GetComponents()->back())->setPosition(SDL_Point{ x, y });
	return holder;
}

std::shared_ptr<Entity> GrassTileFactory::GroundC(std::string textureID, int x, int y)
{
	std::shared_ptr<Entity> holder = std::shared_ptr<Entity>(new Entity("Flowers"));
	holder->AddComponent(std::shared_ptr<SpriteComponent>(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 2)));
	holder->AddComponent(std::shared_ptr<RectangleComponent>(new RectangleComponent()));
	std::static_pointer_cast<RectangleComponent>(holder->GetComponents()->back())->setPosition(SDL_Point{ x, y });
	return holder;
}

std::shared_ptr<Entity> GrassTileFactory::GroundD(std::string textureID, int x, int y)
{
	std::shared_ptr<Entity> holder = std::shared_ptr<Entity>(new Entity("Dirt"));
	holder->AddComponent(std::shared_ptr<SpriteComponent>(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 3)));
	holder->AddComponent(std::shared_ptr<RectangleComponent>(new RectangleComponent()));
	std::static_pointer_cast<RectangleComponent>(holder->GetComponents()->back())->setPosition(SDL_Point{ x, y });
	return holder;
}