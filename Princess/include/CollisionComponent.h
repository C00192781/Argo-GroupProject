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
		m_previousX = x;
		m_previousY = y;
		m_width = width;
		m_height = height;
		m_type = "collision";
	};

	CollisionComponent(float x, float y, float width, float height, float offset)
	{
		m_offset = offset;
		m_x = x + offset;
		m_y = y + offset;
		m_previousX = x + offset;
		m_previousY = y + offset;
		m_width = width;//- m_offset;//(m_offset * 2);
		m_height = height; //- m_offset;//(m_offset * 2);
		m_type = "collision";
	};

	~CollisionComponent() {};

	void setPosition(float xPos, float yPos) { m_x = xPos; m_y = yPos; };
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void setPreviousPosition(float previousX, float previousY) { m_previousX = previousX; m_previousY = previousY; }
	void setPreviousX(float x) { m_previousX = x; }
	void setPreviousY(float y) { m_previousY = y; }
	void setWidth(float width) { m_width = width; }
	float setHeight(float height) { m_height = height; }

	float getX() { return m_x; }
	float getPreviousX() { return m_previousX; }
	float getPreviousY() { return m_previousY; }
	float getY() { return m_y; }
	float getWidth() { return m_width * 3; } // 3 = scale of sprite
	float getHeight() { return m_height * 3; }// 3 = scale of sprite

private:
	float m_x, m_y;
	float m_previousX, m_previousY;
	float m_width, m_height;
	float m_offset;
};
#endif
