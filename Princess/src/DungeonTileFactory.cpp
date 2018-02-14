#include "DungeonTileFactory.h"

Entity* DungeonTileFactory::Wall(std::string textureID, int x, int y, int scale)
{
	Entity* temp = new Entity("Wall");
	temp->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 0));
	temp->AddComponent(new PositionComponent(x * 16 * scale, y * 16 * scale));
	temp->AddComponent(new CollisionComponent(x * 16, y * 16, 16, 16));
	temp->Active(true);

	return temp;
}

Entity* DungeonTileFactory::Floor(std::string textureID, int x, int y, int scale)
{
	Entity* temp = new Entity("Floor");
	temp->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 1));
	temp->AddComponent(new PositionComponent(x * 16 * scale, y * 16 * scale));
	temp->Active(true);

	return temp;
}

Entity* DungeonTileFactory::Grass(std::string textureID, int x, int y, int scale)
{
	Entity* temp = new Entity("Grass");
	temp->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 2));
	temp->AddComponent(new PositionComponent(x * 16 * scale, y * 16 * scale));
	temp->Active(true);

	return temp;
}