#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Entity.h"

class Character
{
public:
	virtual Entity* CharA(std::string ID, SDL_Point pos, int personality) = 0;
	virtual Entity* CharB(std::string ID, SDL_Point pos, int personality) = 0;
	virtual Entity* CharC(std::string ID, SDL_Point pos, int personality) = 0;
	virtual Entity* CharD(std::string ID, SDL_Point pos, int personality) = 0;
};
#endif