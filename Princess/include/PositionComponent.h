#ifndef _POSITIONCOMPONENT_H
#define _POSITIONCOMPONENT_H

#include "Component.h"
class PositionComponent : public Component
{
public:
	PositionComponent()
	{
		m_type = "PC";
		m_x = 0;
		m_y = 0;
	};

	PositionComponent(SDL_Point pos)
	{
		m_type = "PC";
		m_x = pos.x;
		m_y = pos.y;
	};

	PositionComponent(float x, float y)
	{
		m_type = "PC";
		m_x = x;
		m_y = y;
	}

	~PositionComponent() {};

	//SDL_Point getPosition() { return m_pos; };
	float getX() { return m_x; }
	float* getXRef() { return &m_x; }
	float getY() { return m_y; }
	float* getYRef() { return &m_y; }

	//SDL_Point getPosition() { return SDL_Point{ m_x, m_y }; }

	void setPosition(float x, float y) { 
		m_x = x; 
		m_y = y;
	}
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }

private:
	float m_x;
	float m_y;
};
#endif

