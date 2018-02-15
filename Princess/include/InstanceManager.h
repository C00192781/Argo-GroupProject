#include "Instance.h"
#include "StartInstance.h"
#include "BattleMap.h"

class InstanceManager
{
public:
	InstanceManager(StateManager * stateManager, ResourceManager * resourceManager, InputHandler *input,EventListener * eventListener, SDL_Renderer * sdlr, SystemManager * systemManager);
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
		int activeInstance;
};

