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
		m_offset = 0;
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_type = "collision";
	};

	CollisionComponent(float x, float y, float width, float height, float offset)
	{
		m_offset = offset;
		m_x = x + offset;
		m_y = y + offset;
		m_width = width;//- m_offset;//(m_offset * 2);
		m_height = height; //- m_offset;//(m_offset * 2);
		m_type = "collision";
	};

	~CollisionComponent() {};

	void setPosition(float xPos, float yPos) { m_x = xPos; m_y = yPos; };
	void setWidth(float width) { m_width = width; }
	float setHeight(float height) { m_height = height; }

	float getX() { return m_x; }
	float getY() { return m_y; }
	float getWidth() { return m_width * 3; } // 3 = scale of sprite
	float getHeight() { return m_height * 3; }// 3 = scale of sprite

private:
	float m_x, m_y;
	float m_width, m_height;
	float m_offset;
};
#endif
