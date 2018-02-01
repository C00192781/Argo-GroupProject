#ifndef _POSITIONCOMPONENT_H
#define _POSITIONCOMPONENT_H

#include "Component.h"
class PositionComponent : public Component
{
public:
	PositionComponent()
	{
		m_type = "PC";
		m_xPos = 0;
		m_yPos = 0;
	};

	PositionComponent(float x, float y)
	{
		m_type = "PC";
		m_xPos = x;
		m_yPos = y;
	};

	~PositionComponent() {};

	void setPosition(float x, float y)
	{
		m_xPos = x;
		m_yPos = y;
	}

	void setX(float x) { m_xPos = x; }
	float getX() { return m_xPos;  }

	void setY(float y) { m_xPos = y; }
	float getY() { return m_yPos; }

private:
	float m_xPos;
	float m_yPos;
};
#endif

