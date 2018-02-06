#ifndef _COLLISIONCOMPONENT_H
#define _COLLISIONCOMPONENT_H

#include "Component.h"
class CollisionComponent : public Component
{
public:
	CollisionComponent()
	{
		m_width = 0.0f;
		m_width = 0.0f;
		m_type = "collision";

	};

	CollisionComponent(float width, float height)
	{
		m_width = width;
		m_width = height;
		m_type = "collision";
	};

	~CollisionComponent() {};

	void Width(float width) { m_width = width; }
	void Height(float height) { m_height = height; }
	float Width() { return m_width; };
	float Height() { return m_height; };

private:
	float m_width, m_height;

};
#endif

