#ifndef _BASICENEMY_H
#define _BASICENEMY_H

#include "Character.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "AiLogicComponent.h"
#include "MovementComponent.h"
#include "SeekComponent.h"
#include "AttackComponent.h"
#include "AttributesComponent.h"
#include "CollisionComponent.h"
#include "CurrencyComponent.h"
#include "WeaponComponent.h"

class BasicEnemy : public Character
{
public:
	Entity* CharA(std::string ID, SDL_Point pos, int element);
	Entity* CharB(std::string ID, SDL_Point pos, int element);
	Entity* CharC(std::string ID, SDL_Point pos, int element);
	Entity* CharD(std::string ID, SDL_Point pos, int element);

};
#endif

