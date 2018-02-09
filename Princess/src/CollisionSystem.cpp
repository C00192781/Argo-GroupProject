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
		if (m_entities.at(i)->Active()) 
		{
			int collisionKey1 = -1;
			int scKey = -1;

			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "collision")
				{
					collisionKey1 = j;
				}
				else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					scKey = j;
				}
			}

			if (collisionKey1 >= 0)
			{
				SDL_Rect rect1 = { static_cast<CollisionComponent*>(m_entities.at(i)->GetComponents()->at(collisionKey1))->getX(), 
					static_cast<CollisionComponent*>(m_entities.at(i)->GetComponents()->at(collisionKey1))->getY(), 
					static_cast<CollisionComponent*>(m_entities.at(i)->GetComponents()->at(collisionKey1))->getWidth(), 
					static_cast<CollisionComponent*>(m_entities.at(i)->GetComponents()->at(collisionKey1))->getHeight() };

				//if (m_entities.at(i)->ID() == "Player")
				//{
				//	std::cout << "X col: " << rect1.x << std::endl;
				//	//std::cout << "X spr: " << rect1Sprite.x << std::endl;
				//}

				collidableEntities.clear();

				m_quadtree->retrieve(collidableEntities, m_entities.at(i));

				if (!collidableEntities.empty())
				{
					for (int j = 0; j < collidableEntities.size(); j++)
					{
						//if (m_entities.at(i)->ID() == "Projectile" && collidableEntities.at(j)->ID() != "Projectile" && collidableEntities.at(j)->ID() != "Player")
						if (m_entities.at(i) != collidableEntities.at(j)) {
							if (m_entities.at(i)->ID() == "Princess")
							{
								int collisionKey2 = -1;

								for (int k = 0; k < collidableEntities.at(j)->GetComponents()->size(); k++)
								{
									if (collidableEntities.at(j)->GetComponents()->at(k)->Type() == "collision")
									{
										collisionKey2 = k;
									}
								}

								if (collisionKey2 >= 0)
								{
									SDL_Rect rect2 = { static_cast<CollisionComponent*>(collidableEntities.at(j)->GetComponents()->at(collisionKey2))->getX(),
										static_cast<CollisionComponent*>(collidableEntities.at(j)->GetComponents()->at(collisionKey2))->getY(),
										static_cast<CollisionComponent*>(collidableEntities.at(j)->GetComponents()->at(collisionKey2))->getWidth(),
										static_cast<CollisionComponent*>(collidableEntities.at(j)->GetComponents()->at(collisionKey2))->getHeight() };

									SDL_Rect temp{ 0, 0, 0, 0 };

									if (SDL_IntersectRect(&rect1, &rect2, &temp))
									{
										std::cout << m_entities.at(i)->ID() << " -> " << collidableEntities.at(j)->ID() << std::endl;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


