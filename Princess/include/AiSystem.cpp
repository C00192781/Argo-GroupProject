#include "AISystem.h"

void AISystem::addEntity(Entity *e)
{
	entities.push_back(e);
}

void AISystem::update()
{

	for (auto i = entities.begin(), e = entities.end(); i != e; i++)
	{

		for (int j = 0; j < (*i)->GetComponents()->size(); j++) {

			if ((*i)->GetComponents()->at(j)->Type() == "PC") //if current entity component has a position
			{
				// static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X(), 
				static_cast<PositionComponent*>((*i)->GetComponents()->at(j))->X(16);

				//std::cout << "AI update Pos" << std::endl;
			}

			else if ((*i)->GetComponents()->at(j)->Type() == "PC") //if current entity component has a SOMETHING
			{
			//	std::cout << "AI update HP" << std::endl;

			}
		}
	}

}


