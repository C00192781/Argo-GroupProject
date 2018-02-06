#pragma once

#include "Component.h"
class RectangleComponent : public Component
{
public:
	RectangleComponent()
	{
		m_type = "rectangle";
		m_pos = { 0, 0 };
		m_width = 16;
		m_height = 16;
	};

	RectangleComponent(SDL_Point pos, int width, int height)
	{
		m_type = "rectangle";
		m_pos = pos;
		m_width = width;
		m_height = height;
	};

	~RectangleComponent() {};

	SDL_Point getPosition() { return m_pos; };
	SDL_Point* getPositionPtr() { return &m_pos; };
	int getWidth() { return m_width; };
	int getHeight() { return m_height; };

	void setPosition(SDL_Point pos) { m_pos = pos; }
	void setX(float x) { m_pos.x = x; }
	void setY(float y) { m_pos.y = y; }
	void setWidth(float width) { m_width = width; };
	void setHeight(float height) { m_height = m_height; };

private:
	SDL_Point m_pos;
	float m_width;
	float m_height;
};

