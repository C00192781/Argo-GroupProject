#ifndef _CURRENCYMOMENTO_H
#define _CURRENCYMOMENTO_H

class CurrencyMomento
{
public:
	CurrencyMomento(int value) :m_value(value) {};
	~CurrencyMomento() {};

	int Value() { return m_value; };
	void Value(int value) { m_value = value; };
private:
	int m_value;
};


#endif