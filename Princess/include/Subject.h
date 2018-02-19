#pragma once
#include <vector>
#include <list>
#include "ConcreteObserver.h"

class Subject
{
	// list to keep track of all of the achievements we are observing
	std::vector<ConcreteObserver*> list;

public:
	void AttachObserver(ConcreteObserver *achievement);
	void DetachObserver(ConcreteObserver *achievement);
	void Notify(bool activated);
};