#pragma once

#include "Component.h"

class NetworkIDComponent : public Component
{
public:
	NetworkIDComponent() {}
	NetworkIDComponent(int id)
	{
		m_type = "network";
		m_id = id;
	}

	int getID() { return m_id; }

private:
	int m_id;
};