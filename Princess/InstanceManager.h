#include "Instance.h"

class InstanceManager
{
public:
	InstanceManager();
	~InstanceManager();

	void Update();

private:
		std::vector<Entity*> m_instances;
		StateManager * m_stateManager;
		ResourceManager * m_resourceManager;
		InputHandler *input;
		EventListener *listener;
};

