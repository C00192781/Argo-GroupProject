#pragma once
#include "stdafx.h"
#include <list>
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
using namespace std;

class Quadtree 
{
public:
	Quadtree(int pLevel, SDL_Rect pBounds)
	{
		level = pLevel;
		bounds = pBounds;
	}
	~Quadtree();
	
	void clear();
	void split();
	void insert(Entity* entities);
	int getIndex(Entity* entity);
	std::vector<Entity*> retrieve(std::vector<Entity*> &returnObjects, Entity* entity);
	void updateBounds(SDL_Rect b) { bounds = b; }

private:
	int MAX_OBJECTS = 16;
	int MAX_LEVELS = 10;

	int level;
	std::vector<Entity*> objects;
	SDL_Rect bounds;
	std::vector<Quadtree*> nodes;
};