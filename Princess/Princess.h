#ifndef _PRINCESS_H
#define _PRINCESS_H

#include "Character.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "AiLogicComponent.h"
class Princess : public Character
{
public:
	Entity* PrincessEntity(std::string ID, SDL_Point pos, int personality);
};
#endif

