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
	~PositionComponent() {};

	int X() { return m_x; };
	void X(int x) { m_x = x; };

	int Y() { return m_y; };
	void Y(int x) { m_y = x; };

private:
	int m_x, m_y;
};
#endif

