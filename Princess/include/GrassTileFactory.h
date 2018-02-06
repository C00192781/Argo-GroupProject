#ifndef _GRASSTILEFACTORY_H
#define _GRASSTILEFACTORY_H

#include "TileFactory.h"
#include "SpriteComponent.h"
#include "RectangleComponent.h"
class GrassTileFactory : public TileFactory
{
public:
	std::shared_ptr<Entity> GroundA(std::string textureID, int x, int y);
	std::shared_ptr<Entity> GroundB(std::string textureID, int x, int y);
	std::shared_ptr<Entity> GroundC(std::string textureID, int x, int y);
	std::shared_ptr<Entity> GroundD(std::string textureID, int x, int y);
};
#endif

