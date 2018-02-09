#include "DungeonTileFactory.h"

Entity* DungeonTileFactory::GroundA(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Planes");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 0));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
Entity* DungeonTileFactory::GroundB(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Meadow");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 1, 0, 16, 16, 0));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
Entity* DungeonTileFactory::GroundC(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Forest");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 2, 0, 16, 16, 0));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
Entity* DungeonTileFactory::GroundD(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Forest");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 2, 0, 16, 16, 0));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
