#ifndef _GRASSTILEFACTORY_H
#define _GRASSTILEFACTORY_H

#include "TileFactory.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
class GrassTileFactory : public TileFactory
{
public:
	Entity* GroundA(std::string textureID, int x, int y);
	Entity* GroundB(std::string textureID, int x, int y);
	Entity* GroundC(std::string textureID, int x, int y);
	Entity* GroundD(std::string textureID, int x, int y);
};
#endif

