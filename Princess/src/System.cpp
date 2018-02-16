#include "System.h"

void System::AddEntity(Entity * e)
{
	m_entities.push_back(e);
	LoadComponent();
}

Entity* System::FindEntity(std::string id)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == id)
		{
			return m_entities.at(i);
		}
	}

	return nullptr;
}

void System::RemoveEntity(std::string id)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == id)
		{
			m_entities.erase(m_entities.begin() + i);
			m_entities.shrink_to_fit();
			UnloadComponent(i);
		}
	}
}
void System::SelectiveClear()
{
	for (int i = 0; i < m_entities.size();)
	{
		if (!m_entities.at(i)->Transient())
		{
			m_entities.erase(m_entities.begin() + i);
			UnloadComponent(i);
		}
		else
		{
			i++;
		}
	}
	m_entities.shrink_to_fit();
}
void System::FullClear()
{
	m_entities.clear();
	for (int i = 0; i < m_entities.size(); i++)
	{
		UnloadComponent(i);
	}
	m_entities.shrink_to_fit();
}