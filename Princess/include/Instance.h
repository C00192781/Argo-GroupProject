#ifndef _INSTANCE_H
#define _INSTANCE_H

#include <string>
#include "GrassTileFactory.h"
#include "StateManager.h"
#include "SystemManager.h"
#include "Entity.h"
#include "stdafx.h"

class Instance
{
public:
	Instance() {};
	~Instance() {};

	virtual void Update() = 0;

	std::string ID() { return m_id; };
	bool Active() { return m_active; }
	void Active(bool active) { m_active = active; }
	void Clear() { m_systemManager->MassSelectiveClear(); };

protected:
	std::string m_id;

	std::vector<Entity*> m_entities;

	SystemManager * m_systemManager;

	StateManager * m_stateManager;

	bool m_active;
};
#endif