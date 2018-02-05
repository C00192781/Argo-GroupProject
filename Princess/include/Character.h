#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Entity.h"

class Character
{
public:
	virtual Entity* CharA(std::string ID, SDL_Point pos, int personality) = 0;
};
#endif