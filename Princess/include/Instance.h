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
	virtual void Render() = 0;

	std::string ID() { return m_id; };

protected:
	std::string m_id;

	std::vector<Entity*> m_entities;

	SystemManager * m_systemManager;

	StateManager * m_stateManager;
};
#endif