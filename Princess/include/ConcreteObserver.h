#pragma once
#include <iostream>
#include <string>
#include "Observer.h"

class ConcreteObserver : Observer
{
	std::string name;
	bool activated;
public:
	ConcreteObserver(std::string name);
	void Update(bool activated);
};
