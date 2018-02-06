#pragma once

//#include <SDL.h>
//#include "Entity.h"
//#include "RectangleComponent.h"
//
//class Quadtree
//{
//public:
//	Quadtree() {}
//	Quadtree(int depth, SDL_Rect bounds);
//
//	void init();
//
//	void insert(Entity *e);
//	void split();
//	std::vector<Entity*> retrieve(std::vector<Entity*> entities, Entity* e);
//	int getIndex(Entity *e);
//	void clear();
//
//private:
//	int m_maxEntities = 10; // max entities in a node before it splits
//	int m_maxSubnodeDepth = 10; // max amount of subnodes
//
//	int m_currentNodeDepth;
//	SDL_Rect m_bounds; // bounds of node
//	//Quadtree* m_nodes[4]; // subnodes of quadtree
//	std::vector<Quadtree*> m_nodes;
//	std::vector<Entity*> m_entities; // vector of entities that are within the node
//};

#pragma once
#include "stdafx.h"
#include <list>
#include "Entity.h"
#include "RectangleComponent.h"
#include "SpriteComponent.h"
using namespace std;

class Quadtree
{

public:
	Quadtree() {}
	Quadtree(int pLevel, SDL_Rect pBounds)
	{
		level = pLevel;
		bounds = pBounds;
		//nodes.reserve(300);
		//nodes = new Quadtree[4];

	}

	void init();
	void clear();
	void split();
	void insert(Entity* entities);
	int getIndex(Entity* entity);
	std::vector<Entity*> retrieve(std::vector<Entity*> returnObjects, Entity* entity);


private:
	int MAX_OBJECTS = 2;
	int MAX_LEVELS = 5;

	int level;
	std::vector<Entity*> objects;
	SDL_Rect bounds;
	std::vector<Quadtree*> nodes;

	/*
	* Constructor
	*/

};