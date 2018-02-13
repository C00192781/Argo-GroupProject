#include "DungeonTileFactory.h"

Entity* DungeonTileFactory::Wall(std::string textureID, int x, int y)
{
	Entity* temp = new Entity("Wall");
	temp->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 16, 16, 16, 0));
	temp->AddComponent(new PositionComponent(x * 16 * 3, y * 16 * 3));
	//temp->AddComponent(new CollisionComponent(x * 16, y * 16, 16, 16));
	temp->Active(true);

	return temp;
}

Entity* DungeonTileFactory::WallTop(std::string textureID, int x, int y)
{
	Entity* temp = new Entity("WallTop");
	temp->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 0));
	temp->AddComponent(new PositionComponent(x * 16 * 3, y * 16 * 3));
	//temp->AddComponent(new CollisionComponent(x, y, 16, 16));
	temp->Active(true);

	return temp;
}

Entity* DungeonTileFactory::Floor(std::string textureID, int x, int y)
{
	Entity* temp = new Entity("Floor");
	temp->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 32, 16, 16, 0));
	temp->AddComponent(new PositionComponent(x * 16 * 3, y * 16 * 3));
	//temp->AddComponent(new CollisionComponent(x, y, 16, 16));
	temp->Active(true);

	return temp;
}

Entity* DungeonTileFactory::Grass(std::string textureID, int x, int y)
{
	Entity* temp = new Entity("Grass");
	temp->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 48, 16, 16, 0));
	temp->AddComponent(new PositionComponent(x * 16 * 3, y * 16 * 3));
	//temp->AddComponent(new CollisionComponent(x, y, 16, 16));
	temp->Active(true);

	return temp;
}