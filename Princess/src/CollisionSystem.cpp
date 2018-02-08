#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
	m_quadtree = new Quadtree(0, SDL_Rect{ 0, 0, 812, 624 });
}

CollisionSystem::CollisionSystem(SDL_Rect bounds)
{
	m_bounds = bounds;
	m_quadtree = new Quadtree(0, m_bounds);
}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::Update()
{
	std::vector<Entity*> collidableEntities;// = new std::vector<Entity*>;

	m_quadtree->clear();
	m_quadtree->init();

	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->Active())
		{
			m_quadtree->insert(m_entities.at(i));
		}
	}

	for (int i = 0; i < m_entities.size(); i++)
	{
		int pcKey1 = -1;

		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				pcKey1 = j;
			}
		}

		if (pcKey1 >= 0)
		{
			SDL_Rect rect1 = { static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey1))->getX(), static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey1))->getY(), 16, 16 };

			collidableEntities.clear();

			m_quadtree->retrieve(collidableEntities, m_entities.at(i));

			if (!collidableEntities.empty())
			{
				for (int j = 0; j < collidableEntities.size(); j++)
				{
					int pcKey2 = -1;

					for (int k = 0; k < collidableEntities.at(j)->GetComponents()->size(); k++)
					{
						if (collidableEntities.at(j)->GetComponents()->at(k)->Type() == "PC")
						{
							pcKey2 = k;
						}
					}

					if (pcKey2 >= 0)
					{
						SDL_Rect rect2 = { static_cast<PositionComponent*>(collidableEntities.at(j)->GetComponents()->at(pcKey2))->getX(), static_cast<PositionComponent*>(collidableEntities.at(j)->GetComponents()->at(pcKey1))->getY(), 16, 16 };
					
						// COLLISION STUFF
					}
				}
			}
		}
	}
}


