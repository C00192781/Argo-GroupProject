#include "AISystem.h"


AiSystem::AiSystem()
{
	//m_thingy = 1;
}


AiSystem::~AiSystem()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
		m_entities.erase(m_entities.begin() + i);
		m_entities.shrink_to_fit();
	}
}


void AiSystem::Spawn()
{
	/*m_entities.clear();
	m_entities.push_back(m_entities);*/
	//TileFactory * m_factory;
	//m_entities.push_back(new Character)

	SDL_Point p{ 0,0 };

	characterFactory = new Princess();
	m_entities.push_back(characterFactory->CharA("Red", p, 0));

	//m_entities.push_back(CharFactory);
}


void AiSystem::Spawn(std::vector<Entity*> entities)
{
	/*m_entities.clear();
	m_entities.push_back(m_entities);*/
	//TileFactory * m_factory;

	//m_entities.push_back(new Princess());
	//
	//CharFactory.push_back(new Princess());

	
}

std::vector<Entity*> AiSystem::getEntities()
{
	return m_entities;
}


void AiSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int pcKey = -1;
		int ailKey = -1;
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC") //position comp
			{
				pcKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "AIL") //ai logic comp
			{
				ailKey = j;
			}
		}
		if (pcKey >= 0 && ailKey >= 0)
		{
			if (m_entities.at(i)->ID() == "Princess")
			{
				//if it's a princess, do something special
			}

			static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Speed(1); //set speed

			SDL_Point holder{ static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().x, static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition().y };
			//update position with speed
			holder.x += static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Speed();
			holder.y += static_cast<AiLogicComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Speed();

			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->setPosition(holder);

		}
	}
}