#pragma once

#include "Component.h"
class SeekComponent : public Component
{
public:
	SeekComponent()
	{
		m_type = "seek";
		m_xDest = 0;
		m_yDest = 0;
	};

	SeekComponent(float x, float y)
	{
		m_type = "seek";
		m_xDest = x;
		m_yDest = y;
	};

	~SeekComponent() {};

	void setDestination(float x, float y)
	{
		m_xDest = x;
		m_yDest = y;
	}

	float getXDestination() { return m_xDest; };
	float getYDestination() { return m_yDest; };

	void setXDestination(float x) { m_xDest = x; };
	void setYDestination(float y) { m_yDest = y; };

private:
	float m_xDest;
	float m_yDest;
};