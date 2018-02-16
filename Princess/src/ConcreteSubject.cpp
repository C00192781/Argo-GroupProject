#include "ConcreteSubject.h"

void ConcreteSubject::ChangeStatus(bool activate)
{
	Notify(activate);
}
