#ifndef _CURRENCYCOMPONENT_H
#define _CURRENCYCOMPONENT_H

#include "Component.h"
class CurrencyComponent : public Component
{
public:
	CurrencyComponent()
	{
		m_type = "currency";
		m_value = 0;
	};

	CurrencyComponent(int value)
	{
		m_type = "currency";
		m_value = value;
	};

	~CurrencyComponent() {};

	int value() { return m_value; }
	void value(int x) { m_value = x; }
	void incrementValue(int x) { m_value += x; }
private:
	int m_value = 0;
};
#endif

