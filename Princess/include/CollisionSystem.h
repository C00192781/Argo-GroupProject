#pragma once

#include "System.h"
#include "RectangleComponent.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Quadtree.h"

class CollisionSystem : public System
{
public:
	CollisionSystem() {}
	CollisionSystem(SDL_Rect bounds);
	~CollisionSystem();

	void Update();
private:
	SDL_Rect m_bounds;
	Quadtree* m_quadtree;
};