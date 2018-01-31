#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "stdafx.h"

class Component
{
public:
	std::string Type() { return m_type; };
	void Type(std::string x) { m_type = x; };
protected:
	std::string m_type;
};
#endif

