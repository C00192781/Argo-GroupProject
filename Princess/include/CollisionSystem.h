#pragma once

#include "System.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "WeaponComponent.h"
#include "SpriteComponent.h"
#include "Quad.h"
#include "AttributesComponent.h"
#include "ProjectileComponent.h"
#include "CurrencyComponent.h"

#include "EventListener.h"
class CollisionSystem : public System
{
public:
	CollisionSystem();
	CollisionSystem(EventListener* listener);
	CollisionSystem(SDL_Rect bounds, EventListener* listener);
	~CollisionSystem();

	void LoadComponent();
	void UnloadComponent(int x);

	void Update();

	void updateBounds(SDL_Rect bounds);
	Entity* getCurrentDungeon() { return m_currentDungeon; }
private:
	SDL_Rect m_bounds;
	Quadtree* m_quadtree;
	EventListener* m_listener;

	std::vector<Entity*> m_collidableEntities;
	Entity* m_currentDungeon;

	void filterCollisions(int entityIndex, int entityColIndex, int collidableIndex, int collidableColIndex);
	void projectileCollision(int index);
	void spellcasterCollision(int index);
	void pickupCollision(int index, int entityIndex);
};