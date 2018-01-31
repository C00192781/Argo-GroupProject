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
			delete m_entities.at(i);
			m_entities.erase(m_entities.begin() + i);
			m_entities.shrink_to_fit();
			return;
		}
	}
	std::cout << "Could not delete " << id << " as it does not exist!" << std::endl;
}
