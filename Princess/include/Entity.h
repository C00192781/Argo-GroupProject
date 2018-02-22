#ifndef _ENTITY_H
#define _ENTITY_H

#include "Component.h"
#include <vector>
#include "stdafx.h"
#include <cstring>
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
	bool Transient() { return m_transient; };
	void Transient(bool x) { m_transient = x; };
	Component* FindComponent(std::string ID);
	int FindComponentIndex(std::string ID);
	bool Control() { return m_control; };
	void Control(bool x) { m_control = x; };
private:
	std::vector<Component*> m_components;
	std::string m_id;
	bool m_transient;
	bool m_active;
	bool m_control;
};

#endif