#ifndef _PICKUP_H
#define _PICKUP_H

#include "PickupFactory.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "CurrencyComponent.h"
#include "CollisionComponent.h"


class Pickup : public PickupFactory
{
public:
	Entity* PickupA(std::string ID, SDL_Point pos, int value);
	Entity* PickupB(std::string ID, SDL_Point pos, int value);
	Entity* PickupC(std::string ID, SDL_Point pos, int value);
	Entity* PickupD(std::string ID, SDL_Point pos, int value);

};
#endif

