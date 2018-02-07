#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "WeaponComponent.h"
#include "SpriteComponent.h"
#include "Quad.h"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	CollisionSystem(SDL_Rect bounds);
	~CollisionSystem();

	void Update();
private:
	SDL_Rect m_bounds;
	Quadtree* m_quadtree;
};