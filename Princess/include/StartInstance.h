#include "Instance.h"

class StartInstance : public Instance
{
public:
	StartInstance(SystemManager * sm, SDL_Renderer * sdlr, StateManager * s);
	~StartInstance();
	void Begin();
	void Update();
private:

};