#include "CollisionSystem.h"
#include <iostream>

CollisionSystem::CollisionSystem(SDL_Rect bounds)
{
	m_bounds = bounds;
	m_quadtree = new Quadtree(0, bounds);
	m_quadtree->init();
}

CollisionSystem::~CollisionSystem()
{
	
}

void CollisionSystem::Update()
{
	m_quadtree->clear();
	m_quadtree->init();

	for (int i = 0; i < m_entities.size(); i++)
	{
		m_quadtree->insert(m_entities.at(i));
	}
}

