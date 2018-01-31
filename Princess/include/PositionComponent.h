#ifndef _POSITIONCOMPONENT_H
#define _POSITIONCOMPONENT_H

#include "Component.h"
class PositionComponent : public Component
{
public:
	PositionComponent()
	{
		m_type = "PC";
		m_pos = { 0, 0 };
	};

	PositionComponent(SDL_Point pos)
	{
		m_type = "PC";
		m_pos = pos;
	};

	~PositionComponent() {};

	SDL_Point getPosition() { return m_pos; };
	void setPosition(SDL_Point pos) { m_pos = pos; }
	void setX(float x) { m_pos.x = x; }
	void setY(float y) { m_pos.y = y; }

private:
	SDL_Point m_pos;
};
#endif

