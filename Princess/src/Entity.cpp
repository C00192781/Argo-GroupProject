#include "Entity.h"

Entity::Entity(std::string id)
{
	m_id = id;
}

Entity::~Entity()
{
	//for (int i = 0; i < m_components.size(); i++)
	//{
	//	delete m_components.at(i);
	//}
}

void Entity::AddComponent(std::shared_ptr<Component> c)
{
	m_components.push_back(c);
}

void Entity::RemoveComponent(std::shared_ptr<Component> c)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		if (typeid(m_components.at(i)) == typeid(c))
		{
			m_components.erase(m_components.begin() + i);
		}
	}
}