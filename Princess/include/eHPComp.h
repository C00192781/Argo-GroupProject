#pragma once
#ifndef _EHPCOMP_H
#define _EHPCOMP_H

#include "Component.h"
class eHPComp : public Component
{
public:
	eHPComp()
	{
		m_type = "eHP";
		m_HP = 5;
		m_MAXHP = 5;
	};

	eHPComp(int hp, int MAXHP)
	{
		m_type = "eHP";
		m_MAXHP = MAXHP;
		m_HP = hp;
	};

	~eHPComp() {};

	int getHP() { return m_HP; }
	int getMAXHP() { return m_MAXHP; }


	void setHP(int hp) { m_HP = hp; }
	void setMAXHP(int maxHP) { m_MAXHP = maxHP; }

private:
	int m_HP;
	int m_MAXHP;
};
#endif

