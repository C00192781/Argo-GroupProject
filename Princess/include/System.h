#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "Entity.h"
#include "stdafx.h"

class System
{
public:

	System() {};
	~System() {};

	void AddEntity(Entity * e);
	void RemoveEntity(std::string id);
	void SelectiveClear();
	void FullClear();
	virtual void Update() = 0;

	bool Active() { return m_active; };
	void Active(bool x) { m_active = x; };

protected:

	std::vector<Entity*> m_entities;
	bool m_active;
};
#endif

