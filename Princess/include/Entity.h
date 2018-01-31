#ifndef _ENTITY_H
#define _ENTITY_H

#include "Component.h"
#include <vector>
#include "stdafx.h"
class Entity
{
public:
	Entity(std::string id);
	~Entity();
	void AddComponent(Component* c);
	void RemoveComponent(Component* c);
	std::vector<Component*>* GetComponents() { return &m_components; };
	std::string ID() { return m_id; };
	bool Active() { return m_active; };
	void Active(bool x) { m_active = x; };
private:
	std::vector<Component*> m_components;
	std::string m_id;
	bool m_active;
};

#endif