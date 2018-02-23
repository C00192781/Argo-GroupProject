#include "Instance.h"

class StartInstance : public Instance
{
public:
	StartInstance(SystemManager * sm, StateManager * s);
	~StartInstance();
	void Generate();
	void Update() {};
private:

};