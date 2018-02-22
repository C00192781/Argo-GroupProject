#include "Entity.h"

Entity::Entity(std::string id)
{
	m_id = id;
	m_active = true;
}

Entity::~Entity()
{
	for (int i = 0; i < m_components.size(); i++)
	{
		delete m_components.at(i);
	}
}

void Entity::AddComponent(Component* c)
{
	m_components.push_back(c);
}

Component* Entity::FindComponent(std::string ID)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		if (m_components.at(i)->Type() == ID)
		{
			return m_components.at(i);
		}
	}

	return nullptr;
}


int Entity::FindComponentIndex(std::string ID)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		if (m_components.at(i)->Type() == ID)
		{
			return i;
		}
	}

	return -1;
}

void Entity::RemoveComponent(Component* c)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		if (typeid(m_components.at(i)) == typeid(c))
		{
			m_components.erase(m_components.begin() + i);
		}
	}
}