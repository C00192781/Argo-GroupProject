#ifndef _CURRENCYCOMPONENT_H
#define _CURRENCYCOMPONENT_H

#include "Component.h"
#include "CurrencyMomento.h"
class CurrencyComponent : public Component
{
public:
	CurrencyComponent()
	{
		m_type = "currency";
		m_value = 0;
		momento = new CurrencyMomento(m_value);
	};

	CurrencyComponent(int value)
	{
		m_type = "currency";
		m_value = value;
		momento = new CurrencyMomento(m_value);
	};

	~CurrencyComponent() {};

	int value() { return m_value; }
	void value(int x) { m_value = x; }
	void incrementValue(int x) { m_value += x; }

	void Save()
	{
		delete momento;
		momento = new CurrencyMomento(m_value);
	}

	void Revert()
	{
		m_value = momento->Value();
	}

private:

	CurrencyMomento * momento;
	int m_value = 0;
};
#endif

