#ifndef _TILEFACTORY_H
#define _TILEFACTORY_H

#include "Entity.h"

class TileFactory
{
public:
	virtual std::shared_ptr<Entity> GroundA(std::string textureID, int x, int y) = 0;
	virtual std::shared_ptr<Entity> GroundB(std::string textureID, int x, int y) = 0;
	virtual std::shared_ptr<Entity> GroundC(std::string textureID, int x, int y) = 0;
	virtual std::shared_ptr<Entity> GroundD(std::string textureID, int x, int y) = 0;
};
#endif