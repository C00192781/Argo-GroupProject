#include "Subject.h"
#include <algorithm>

using namespace std;

void Subject::AttachObserver(ConcreteObserver *achievement)
{
	list.push_back(achievement);
}
void Subject::DetachObserver(ConcreteObserver *achievement)
{
	list.erase(std::remove(list.begin(), list.end(), achievement), list.end());
}

void Subject::Notify(bool activated)
{
	for (vector<ConcreteObserver*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		if (*iter != 0)
		{
			(*iter)->Update(activated);
		}
	}
}