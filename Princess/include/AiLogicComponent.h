#ifndef _AILOGICCOMPONENT_H
#define _AILOGICCOMPONENT_H

#include "Component.h"
class AiLogicComponent : public Component
{
public:
	AiLogicComponent()
	{
		m_type = "AIL";
		m_behaviour = 0;
		m_heading = 0;
		m_speed = 0;
		m_money = 1;
	};
	~AiLogicComponent() {};

	int Behaviour() { return m_behaviour; };
	void Behaviour(int behave) { m_behaviour = behave; };

	int Heading() { return m_heading; };
	void Heading(int heading) { m_heading = heading; };

	int Speed() { return m_speed; };
	void Speed(int speed) { m_speed = speed; };

	int Money() { return m_money; };
	void Money(int money) { m_money = money; };

private:
	int m_behaviour;
	int m_heading;
	int m_speed;
	int m_money;
};

#endif
