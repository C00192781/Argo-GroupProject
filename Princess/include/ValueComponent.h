#ifndef _VALUECOMPONENT_H
#define _VALUECOMPONENT_H
#include "Component.h"

class ValueComponent : public Component
{
private:

	int m_score;
	int m_gold;

public:
	ValueComponent()
	{
		m_score = 0;
		m_gold = 0;
	};

	int Gold() { return m_gold; };
	void Gold(int x) { m_gold = x; };

	int Score() { return m_score; };
	void Score(int x) { m_score = x; };

};
#endif