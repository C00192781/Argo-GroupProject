#ifndef _PRINCESS_H
#define _PRINCESS_H

#include "Character.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "AiLogicComponent.h"
#include "MovementComponent.h"
#include "AttributesComponent.h"
#include "SeekComponent.h"
#include "CollisionComponent.h"

class Princess : public Character
{
public:
	Entity* CharA(std::string ID, SDL_Point pos, int personality);
	Entity* CharB(std::string ID, SDL_Point pos, int personality);
	Entity* CharC(std::string ID, SDL_Point pos, int personality);
	Entity* CharD(std::string ID, SDL_Point pos, int personality);
};
#endif

