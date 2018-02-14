#ifndef _TOWNINSTANCEMANAGER_H
#define _TOWNINSTANCEMANAGER_H

#include "Instance.h"
#include "SystemManager.h"
class TownInstance : public Instance
{
public:
	TownInstance(SystemManager * sys);
	~TownInstance();

	void Generate(std::string type);
	void Load();

	void Update();

private:

	SystemManager * m_systemManager;

};
#endif

