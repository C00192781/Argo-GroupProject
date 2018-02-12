#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "WeaponComponent.h"
#include "SpriteComponent.h"
#include "Quad.h"
#include "AttributesComponent.h"
#include "ProjectileComponent.h"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	CollisionSystem(SDL_Rect bounds);
	~CollisionSystem();
	int x1 = -22222;
	int y1 = -22222;
	int w1 = -22222;
	int h1 = -22222;
	int damage = 0;
	bool collision = false;
	void LoadComponent();
	void UnloadComponent(int x);

	void Update();
private:
	SDL_Rect m_bounds;
	Quadtree* m_quadtree;

	std::vector<Entity*> m_collidableEntities;

	void filterCollisions(int entityIndex, int entityColIndex, int collidableIndex, int collidableColIndex);
	void projectileCollision(int index);
	void spellcasterCollision(int index);
};