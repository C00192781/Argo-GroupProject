#include "GrassTileFactory.h"

Entity* GrassTileFactory::GroundA(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Grass");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 0));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(x, y);
	return holder;
}

Entity* GrassTileFactory::GroundB(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Dirt Holes");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 1));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(x, y);
	return holder;
}

Entity* GrassTileFactory::GroundC(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Flowers");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 2));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(x, y);
	return holder;
}

Entity* GrassTileFactory::GroundD(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Dirt");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 3));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(x, y);
	return holder;
}