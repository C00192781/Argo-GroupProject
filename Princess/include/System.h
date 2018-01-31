#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "Entity.h"
#include "stdafx.h"

class System
{
public:

	void AddEntity(Entity * e);
	void RemoveEntity(std::string id);
	virtual void Update() = 0;

protected:
	std::vector<Entity*> m_entities;
};
#endif

