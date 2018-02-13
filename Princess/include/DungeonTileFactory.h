#pragma once

#include "Entity.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"

class DungeonTileFactory
{
public:
	Entity* Wall(std::string textureID, int x, int y);
	Entity* WallTop(std::string textureID, int x, int y);
	Entity* Floor(std::string textureID, int x, int y);
	Entity* Grass(std::string textureID, int x, int y);
};