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
		m_distToDestination = 999999;
		m_initialization = false;
	};

	SeekComponent(float x, float y)
	{
		m_type = "seek";
		m_xDest = x;
		m_yDest = y;
		m_distToDestination = 999999;
		m_initialization = false;
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

	void setDistanceToDestination(float dist) { m_distToDestination = dist; };
	float getDistanceToDestination() { return m_distToDestination; };

	bool getInitialization() { return m_initialization; };
	void setInitialization(bool initialization) { m_initialization = initialization; }

private:
	float m_xDest;
	float m_yDest;

	float m_distToDestination;
	bool m_initialization;
};