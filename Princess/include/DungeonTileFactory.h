#pragma once

#include "Entity.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"

class DungeonTileFactory
{
public:
	Entity* Wall(std::string textureID, int x, int y, int scale);
	Entity* Floor(std::string textureID, int x, int y, int scale);
	Entity* Grass(std::string textureID, int x, int y, int scale);
	Entity* LeftDoor(std::string textureID, int x, int y, int scale);
	Entity* RightDoor(std::string textureID, int x, int y, int scale);
	Entity* TopDoor(std::string textureID, int x, int y, int scale);
	Entity* BottomDoor(std::string textureID, int x, int y, int scale);
};