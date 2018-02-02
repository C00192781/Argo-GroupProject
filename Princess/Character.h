#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Entity.h"

class Character
{
public:
	virtual Entity* GroundA(std::string textureID, int x, int y) = 0;
	virtual Entity* GroundB(std::string textureID, int x, int y) = 0;
	virtual Entity* GroundC(std::string textureID, int x, int y) = 0;
	virtual Entity* GroundD(std::string textureID, int x, int y) = 0;
};
#endif