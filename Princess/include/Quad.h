#ifndef _QUAD_H
#define _QUAD_H

#include "Entity.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"

class Quad
{
public:
	Quad(int width, int height, int depth);
	~Quad();

	void Fission(std::vector<Entity*>* entities);


private:
	std::vector<std::vector<std::vector<Entity*>>> m_entities;
	int m_width, m_height;
	int m_depth;
	std::vector<SDL_Rect> m_rects;
	int m_dimensions;
	int timeUp = 0;
};
#endif
