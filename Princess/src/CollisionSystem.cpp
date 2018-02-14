#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
	m_quadtree = new Quadtree(0, SDL_Rect{ 0, 0, 812, 624 });
	m_entities.push_back(new Entity("Null"));
	delete m_entities.back();
	m_entities.clear();
}

CollisionSystem::CollisionSystem(SDL_Rect bounds)
{
	m_bounds = bounds;
	m_quadtree = new Quadtree(0, m_bounds);
	m_entities.push_back(new Entity("Null"));
	delete m_entities.back();
	m_entities.clear();
}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::LoadComponent()
{
	//int pcKey = -1;
	//int scKey = -1;
	//for (int j = 0; j < m_entities.back()->GetComponents()->size(); j++)
	//{
	//	if (m_entities.back()->GetComponents()->at(j)->Type() == "PC")
	//	{
	//		pcKey = j;
	//	}
	//	else if (m_entities.back()->GetComponents()->at(j)->Type() == "SC")
	//	{
	//		scKey = j;
	//	}
	//	if (scKey > 0 && pcKey > 0)
	//	{
	//		break;
	//	}
	//}
	//m_positionComponent.push_back(static_cast<PositionComponent>(m_entities.back()->GetComponents()->at(pcKey)));
	//m_spriteComponent.push_back(static_cast<SpriteComponent>(m_entities.back()->GetComponents()->at(scKey)));
}

void CollisionSystem::UnloadComponent(int x)
{
	//m_positionComponent.erase(m_positionComponent.begin() + x);
	//m_spriteComponent.erase(m_spriteComponent.begin() + x);
	//m_positionComponent.shrink_to_fit();
	//m_spriteComponent.shrink_to_fit();
}

void CollisionSystem::Update()
{
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

			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "collision")
				{
					collisionKey1 = j;
				}
			}

			if (collisionKey1 >= 0)
			{
				m_collidableEntities.clear();

				m_quadtree->retrieve(m_collidableEntities, m_entities.at(i));

				if (!m_collidableEntities.empty())
				{
					for (int j = 0; j < m_collidableEntities.size(); j++)
					{
						if (m_collidableEntities.at(j)->Active())
						{
							if (m_entities.at(i) != m_collidableEntities.at(j)) // doesn't collide with itself
							{
								int collisionKey2 = -1;

								for (int k = 0; k < m_collidableEntities.at(j)->GetComponents()->size(); k++)
								{
									if (m_collidableEntities.at(j)->GetComponents()->at(k)->Type() == "collision")
									{
										collisionKey2 = k;
									}
								}

								filterCollisions(i, collisionKey1, j, collisionKey2);
							}
						}
					}
				}
			}
		}
	}
}

void CollisionSystem::filterCollisions(int entityIndex, int entityColIndex, int collidableIndex, int collidableColIndex)
{
	SDL_Rect rectEntity = { static_cast<CollisionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(entityColIndex))->getX(),
		static_cast<CollisionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(entityColIndex))->getY(),
		static_cast<CollisionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(entityColIndex))->getWidth(),
		static_cast<CollisionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(entityColIndex))->getHeight() };

	SDL_Rect rectCollidable = { static_cast<CollisionComponent*>(m_collidableEntities.at(collidableIndex)->GetComponents()->at(collidableColIndex))->getX(),
		static_cast<CollisionComponent*>(m_collidableEntities.at(collidableIndex)->GetComponents()->at(collidableColIndex))->getY(),
		static_cast<CollisionComponent*>(m_collidableEntities.at(collidableIndex)->GetComponents()->at(collidableColIndex))->getWidth(),
		static_cast<CollisionComponent*>(m_collidableEntities.at(collidableIndex)->GetComponents()->at(collidableColIndex))->getHeight() };

	SDL_Rect holder{ 0, 0, 0, 0 };

	if (SDL_IntersectRect(&rectEntity, &rectCollidable, &holder))
	{
		if (m_entities.at(entityIndex)->ID() == "Spellcaster Enemy")
		{
			if (m_collidableEntities.at(collidableIndex)->ID() == "Projectile")
			{
				projectileCollision(collidableIndex);
				spellcasterCollision(entityIndex);
			}
		}
		//else if (m_entities.at(entityIndex)->ID() == "Princess")
		//{
		//
		//}
	}
}

void CollisionSystem::projectileCollision(int index)
{
	// find projectile component in collidable
	// set ttl to 0



	//for (int i = 0; i < m_collidableEntities.at(index)->GetComponents()->size(); i++)
	//{
	//	if (m_collidableEntities.at(index)->GetComponents()->at(i)->Type() == "PJ")
	//	{
	//		static_cast<ProjectileComponent*>(m_collidableEntities.at(index)->GetComponents()->at(i))->setTimeToLive(0);
	//		std::cout << "DE WEI" << std::endl;
	//	}
	//}
}

void CollisionSystem::spellcasterCollision(int index)
{
	//std::cout << "OH NO" << std::endl;
}