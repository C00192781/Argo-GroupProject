#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();

	void Update();
};