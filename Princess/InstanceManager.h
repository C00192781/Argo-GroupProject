#include "Instance.h"
#include "StartInstance.h"

class InstanceManager
{
public:
	InstanceManager(StateManager * stateManager, ResourceManager * resourceManager, InputHandler *input,EventListener * eventListener, SDL_Renderer * sdlr);
	~InstanceManager();

	void Update();

private:
		std::vector<Instance*> m_instances;
		StateManager * m_stateManager;
		ResourceManager * m_resourceManager;
		InputHandler *m_input;
		EventListener *m_eventListener;
		SystemManager * m_systemManager;
		SDL_Renderer * m_sdlr;
};

