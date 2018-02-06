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
	void AddComponent(std::shared_ptr<Component> c);
	void RemoveComponent(std::shared_ptr<Component> c);
	std::vector<std::shared_ptr<Component>>* GetComponents() { return &m_components; };
	std::string ID() { return m_id; };
	bool Active() { return m_active; };
	void Active(bool x) { m_active = x; };
	bool Transient() { return m_transient; };
	void Transient(bool x) { m_transient = x; };
private:
	std::vector<std::shared_ptr<Component>> m_components;
	std::string m_id;
	bool m_transient;
	bool m_active;
};

#endif