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
	int x1 = -22222;
	int y1 = -22222;
	int w1 = -22222;
	int h1 = -22222;
	void Update();
};