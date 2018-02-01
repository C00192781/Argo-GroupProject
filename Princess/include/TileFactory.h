#ifndef _TILEFACTORY_H
#define _TILEFACTORY_H

#include "Entity.h"

class TileFactory
{
public:
	virtual Entity* GroundA(std::string textureID, int x, int y) = 0;
	virtual Entity* GroundB(std::string textureID, int x, int y) = 0;
	virtual Entity* GroundC(std::string textureID, int x, int y) = 0;
	virtual Entity* GroundD(std::string textureID, int x, int y) = 0;
};
#endif