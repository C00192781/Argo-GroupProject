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
	
	~Quadtree()
	{
		for (std::vector<Quadtree*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			delete (*it);
		}

		nodes.clear();
		objects.clear();
	}
	void init();
	void clear();
	void split();
	void insert(Entity* entities);
	int getIndex(Entity* entity);
	std::vector<Entity*> retrieve(std::vector<Entity*> &returnObjects, Entity* entity);

private:
	int MAX_OBJECTS = 10;
	int MAX_LEVELS = 3;

	int level;
	std::vector<Entity*> objects;
	SDL_Rect bounds;
	std::vector<Quadtree*> nodes;
};