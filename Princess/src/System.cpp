#include "System.h"

void System::AddEntity(Entity * e)
{
	m_entities.push_back(e);
}
void System::RemoveEntity(std::string id)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == id)
		{
			m_entities.erase(m_entities.begin() + i);
			m_entities.shrink_to_fit();
		}
	}
}
void System::SelectiveClear()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (!m_entities.at(i)->Transient())
		{
			m_entities.erase(m_entities.begin() + i);
		}
	}
	m_entities.shrink_to_fit();
}
void System::FullClear()
{
	m_entities.clear();
	m_entities.shrink_to_fit();
}