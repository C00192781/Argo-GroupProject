#ifndef _GOLDCOMPONENT_H
#define _GOLDCOMPONENT_H

#include <list>
#include "Component.h"
#include <iostream>

class GoldComponent : public Component
{
public:
	GoldComponent()
	{
		m_type = "Gold";
		m_gold = 0;
	};
	GoldComponent(int x)
	{
		m_type = "Gold";
		m_gold = x;
	};
	~GoldComponent()
	{
	};

	void Gold(int x) { m_gold = x; };
	int Gold() { return m_gold; };

private:
	int m_gold;
};
#endif
