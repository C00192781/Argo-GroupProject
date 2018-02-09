#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "AiLogicComponent.h"
#include "MovementComponent.h"
#include "AttributesComponent.h"
#include "SeekComponent.h"
#include "ControlComponent.h"
class Player : public Character
{
public:
	Entity* Player_Human1(std::string ID, SDL_Point pos, int personality);
	Entity* Player_Human2(std::string ID, SDL_Point pos, int personality);
	Entity* Player_Human3(std::string ID, SDL_Point pos, int personality);
	Entity* Player_Human4(std::string ID, SDL_Point pos, int personality);
	Entity* Player_AI1(std::string ID, SDL_Point pos, int personality);
	Entity* Player_AI2(std::string ID, SDL_Point pos, int personality);
	Entity* Player_AI3(std::string ID, SDL_Point pos, int personality);
	Entity* Player_AI4(std::string ID, SDL_Point pos, int personality);
};
#endif

