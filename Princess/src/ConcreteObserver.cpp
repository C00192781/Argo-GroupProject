#include "ConcreteObserver.h"

ConcreteObserver::ConcreteObserver(std::string name)
{
	this->name = name;
}

void ConcreteObserver::Update(bool activated)
{
	this->activated = activated;

	std::cout << name << " is " << activated << std::endl;
}