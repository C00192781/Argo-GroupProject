#ifndef _PICKUPFACTORY_H
#define _PICKUPFACTORY_H

#include "Entity.h"

class PickupFactory
{
public:
	virtual Entity* PickupA(std::string ID, SDL_Point pos, int value) = 0;
	virtual Entity* PickupB(std::string ID, SDL_Point pos, int value) = 0;
	virtual Entity* PickupC(std::string ID, SDL_Point pos, int value) = 0;
	virtual Entity* PickupD(std::string ID, SDL_Point pos, int value) = 0;
};
#endif