#ifndef _COLLISIONCOMPONENT_H
#define _COLLISIONCOMPONENT_H

#include "Component.h"
class CollisionComponent : public Component
{
public:
	CollisionComponent()
	{
		m_x = 0.0f;
		m_y = 0.0f;
		m_width = 0.0f;
		m_width = 0.0f;
		m_type = "collision";

	};

	CollisionComponent(float x, float y, float width, float height)
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_width = height;
		m_type = "collision";
	};

	~CollisionComponent() {};


	void setPosition(float xPos, float yPos) { m_x = xPos; m_y = yPos; };
	void setWidth(float width) { m_width = width; }
	float setHeight(float height) { m_height = height; }

private:
	float m_x, m_y;
	float m_width, m_height;

};
#endif

