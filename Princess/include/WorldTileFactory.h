#ifndef _WORLDTILEMAP_H
#define _WORLDTILEMAP_H

#include "Entity.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"

class WorldTileFactory
{
public:

	Entity* Planes(std::string textureID, int x, int y);
	Entity* Meadow(std::string textureID, int x, int y);
	Entity* Forest(std::string textureID, int x, int y);

	Entity* Desert(std::string textureID, int x, int y);
	Entity* Dunes(std::string textureID, int x, int y);
	Entity* Rock(std::string textureID, int x, int y);

	Entity* SnowField(std::string textureID, int x, int y);
	Entity* SnowDunes(std::string textureID, int x, int y);
	Entity* Glacier(std::string textureID, int x, int y);

	Entity* Water(std::string textureID, int x, int y);
	Entity* DeepWater(std::string textureID, int x, int y);
	Entity* IceSheet(std::string textureID, int x, int y);

	Entity* Town(std::string textureID, int x, int y);
	Entity* Castle(std::string textureID, int x, int y);
	Entity* Dungeon(std::string textureID, int x, int y);
	Entity* DarkCastle(std::string textureID, int x, int y);

};
#endif

