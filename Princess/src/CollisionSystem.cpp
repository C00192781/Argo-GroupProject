#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
	m_quadtree = new Quadtree(0, SDL_Rect{ 0, 0, 812, 624 });
}

CollisionSystem::CollisionSystem(EventListener* listener)
{
	m_listener = listener;
	m_quadtree = new Quadtree(0, SDL_Rect{ 0, 0, 812, 624 });
}

CollisionSystem::CollisionSystem(SDL_Rect bounds, EventListener* listener)
{
	m_bounds = bounds;
	m_listener = listener;
	m_quadtree = new Quadtree(0, m_bounds);
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

void CollisionSystem::updateBounds(SDL_Rect bounds)
{
	m_bounds = bounds;
	m_quadtree->updateBounds(bounds);
}

void CollisionSystem::Update()
{
	m_quadtree->clear();

	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->Active())
		{
			m_quadtree->insert(m_entities.at(i));
		}
	}

	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->Active() == true && m_entities.at(i)->ID() != "Wall")
		{
			int collisionKey1 = -1;

			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "collision")
				{
					collisionKey1 = j;
					break;
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
										break;
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
	CollisionComponent* entityCol = static_cast<CollisionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(entityColIndex));
	CollisionComponent* collidableCol = static_cast<CollisionComponent*>(m_collidableEntities.at(collidableIndex)->GetComponents()->at(collidableColIndex));

	if ((m_entities.at(entityIndex)->ID() == "Player" || m_entities.at(entityIndex)->ID() == "Spellcaster Enemy" || m_entities.at(entityIndex)->ID() == "Melee Enemy" || m_entities.at(entityIndex)->ID() == "Ranged Enemy") && m_collidableEntities.at(collidableIndex)->ID() == "Wall")
	{
		SDL_Rect rectEntityX = { entityCol->getX(), entityCol->getPreviousY(), entityCol->getWidth(), entityCol->getHeight() };
		SDL_Rect rectEntityY = { entityCol->getPreviousX(), entityCol->getY(), entityCol->getWidth(), entityCol->getHeight() };
		
		SDL_Rect rectCollidable = { collidableCol->getX(), collidableCol->getY(), collidableCol->getWidth(), collidableCol->getHeight() };

		SDL_Rect holder{ 0, 0, 0, 0 };

		if (SDL_IntersectRect(&rectEntityX, &rectCollidable, &holder))
		{
			if (entityCol->getPreviousX() < entityCol->getX())
			{
				entityCol->setX(entityCol->getX() - holder.w);
			}
			else if (entityCol->getPreviousX() > entityCol->getX())
			{
				entityCol->setX(entityCol->getX() + holder.w);
			}
		}

		if (SDL_IntersectRect(&rectEntityY, &rectCollidable, &holder))
		{
			if (entityCol->getPreviousY() < entityCol->getY())
			{
				entityCol->setY(entityCol->getY() - holder.h);
			}
			else if (entityCol->getPreviousY() > entityCol->getY())
			{
				entityCol->setY(entityCol->getY() + holder.h);
			}
		}
	}
	else
	{
		SDL_Rect rectEntity = { entityCol->getX(), entityCol->getY(), entityCol->getWidth(), entityCol->getHeight() };

		SDL_Rect rectCollidable = { collidableCol->getX(), collidableCol->getY(), collidableCol->getWidth(), collidableCol->getHeight() };

		SDL_Rect holder{ 0, 0, 0, 0 };

		if (SDL_IntersectRect(&rectEntity, &rectCollidable, &holder))
		{
			if (m_entities.at(entityIndex)->ID() == "Player")
			{
				projectileCollision(entityIndex);
			//	spellcasterCollision(collidableIndex); //swapped for spell id, WHO CARES IF A PLAYER WALKS INTO AN AI IF THEYRE NOT SHOOTING EACH OTHER
				if (m_collidableEntities.at(collidableIndex)->ID() == "Dungeon")
				{
					if (m_listener->Space || m_listener->AButton)
					{
						m_listener->WorldToDungeon = true;
						m_currentDungeon = m_collidableEntities.at(collidableIndex);
					}
				}
				if (m_collidableEntities.at(collidableIndex)->ID() == "Town")
				{
					if (m_listener->Space || m_listener->AButton)
					{
						m_listener->WorldToTown = true;
						m_currentTown = m_collidableEntities.at(collidableIndex);
					}
				}
				else if (m_collidableEntities.at(collidableIndex)->ID() == "Chocolate" || m_collidableEntities.at(collidableIndex)->ID() == "Jewels" || m_collidableEntities.at(collidableIndex)->ID() == "Gold" || m_collidableEntities.at(collidableIndex)->ID() == "Literature")
				{
					pickupCollision(collidableIndex, entityIndex); //I THINK
				}
			}

			if (m_entities.at(entityIndex)->ID() == "Projectile")
			{
				if (m_collidableEntities.at(collidableIndex)->ID() == "Spellcaster Enemy" || m_collidableEntities.at(collidableIndex)->ID() == "Melee Enemy" || m_collidableEntities.at(collidableIndex)->ID() == "Ranged Enemy")
				{
					ProjectileComponent* projectileComponent = static_cast<ProjectileComponent*>(m_entities.at(entityIndex)->FindComponent("PJ"));
					if (projectileComponent->getShooterType() == "Player")
					{
						projectileCollision(entityIndex);
						spellcasterCollision(collidableIndex);
					}
				}
				else if (m_collidableEntities.at(collidableIndex)->ID() == "Wall")
				{
					projectileCollision(entityIndex);
				}
				else if (m_collidableEntities.at(collidableIndex)->ID() == "Player")
				{
					ProjectileComponent* projectileComponent = static_cast<ProjectileComponent*>(m_entities.at(entityIndex)->FindComponent("PJ"));
					if (projectileComponent->getShooterType() != "Player")
					{
						projectileCollision(entityIndex);
						playerCollision(collidableIndex);
					}
				}
				else if (m_collidableEntities.at(collidableIndex)->ID() == "Princess")
				{
					ProjectileComponent* projectileComponent = static_cast<ProjectileComponent*>(m_entities.at(entityIndex)->FindComponent("PJ"));
					if (projectileComponent->getShooterType() != "Player")
					{
						projectileCollision(entityIndex);
						princessCollision(collidableIndex);
					}
				}
			}
		}
	}
}

void CollisionSystem::projectileCollision(int index)
{
	// find projectile component in collidable
	// set ttl to 0

	ProjectileComponent* p = static_cast<ProjectileComponent*>(m_entities.at(index)->FindComponent("PJ"));

	if (p != nullptr)
	{
		p->setTimeToLive(0);
	}
}

void CollisionSystem::spellcasterCollision(int index)
{
	std::cout << "OH NO" << std::endl;


	auto hpComp = m_collidableEntities.at(index)->FindComponent("attribute");

	if (hpComp != nullptr)
	{


		//auto temp = m_collidableEntities.at(index)->FindComponent("eHP");
		if (static_cast<AttributesComponent*>(hpComp)->Armour() > 0)
		{
			static_cast<AttributesComponent*>(hpComp)->Armour((static_cast<AttributesComponent*>(hpComp)->Armour() - 1));
		}
		else
		{
			static_cast<AttributesComponent*>(hpComp)->Health((static_cast<AttributesComponent*>(hpComp)->Health() - 1));
		}

		if (static_cast<AttributesComponent*>(hpComp)->Health() < 1)
		{
			m_collidableEntities.at(index)->Active(false);
		}
	}
		/*auto tar = m_entities.at(j)->FindComponent("PC");
	tarX = static_cast<PositionComponent*>(tar)->getX();*/
}



void CollisionSystem::playerCollision(int index)
{



	auto hpComp = m_collidableEntities.at(index)->FindComponent("attribute");

	auto moveComp = m_collidableEntities.at(index)->FindComponent("movement");



	if (hpComp != nullptr)
	{
		if (static_cast<MovementComponent*>(moveComp)->getRolling() == false)
		{
			//auto temp = m_collidableEntities.at(index)->FindComponent("eHP");

			if (static_cast<AttributesComponent*>(hpComp)->Armour() > 0)
			{
				static_cast<AttributesComponent*>(hpComp)->Armour((static_cast<AttributesComponent*>(hpComp)->Armour() - 1));
			}
			else
			{
				static_cast<AttributesComponent*>(hpComp)->Health((static_cast<AttributesComponent*>(hpComp)->Health() - 1));
			}

			if (static_cast<AttributesComponent*>(hpComp)->Health() < 1)
			{
				m_collidableEntities.at(index)->Active(false);
			}
			std::cout << "player SLAPPED" << static_cast<AttributesComponent*>(hpComp)->Armour() << static_cast<AttributesComponent*>(hpComp)->Health() << std::endl;
		}
		else
		{
			std::cout << "player DODGED FSDBFSJKDFSD" << std::endl;
		}
	}
	/*auto tar = m_entities.at(j)->FindComponent("PC");
	tarX = static_cast<PositionComponent*>(tar)->getX();*/
}



void CollisionSystem::princessCollision(int index)
{

	auto hpComp = m_collidableEntities.at(index)->FindComponent("attribute");

	auto moveComp = m_collidableEntities.at(index)->FindComponent("movement");



	if (hpComp != nullptr)
	{

		//auto temp = m_collidableEntities.at(index)->FindComponent("eHP");
		static_cast<AttributesComponent*>(hpComp)->Health((static_cast<AttributesComponent*>(hpComp)->Health() - 1));

		if (static_cast<AttributesComponent*>(hpComp)->Health() < 1)
		{
			m_collidableEntities.at(index)->Active(false);
		}
		std::cout << "PRINCESS SLAPPED" << std::endl;
	

	}
	/*auto tar = m_entities.at(j)->FindComponent("PC");
	tarX = static_cast<PositionComponent*>(tar)->getX();*/
}




void CollisionSystem::pickupCollision(int index, int entityIndex)
{
	std::cout << "OH YEESSSS" << std::endl;


	auto valueComp = m_collidableEntities.at(index)->FindComponent("currency");

	int cash = static_cast<CurrencyComponent*>(valueComp)->value();

	

	if (valueComp != nullptr)
	{
		//auto temp = m_collidableEntities.at(index)->FindComponent("eHP");
	//	auto temp = static_cast<CurrencyComponent*>(valueComp)->value(static_cast<CurrencyComponent*>(valueComp)->value() + (static_cast<CurrencyComponent*>(valueComp)->value()));

		auto playerBank = m_entities.at(entityIndex)->FindComponent("currency");

		std::vector<Entity*> projAct;

		for (int i = 0; i < m_entities.size(); i++)
		{
			if (m_entities.at(i)->ID() == "Projectile" && m_entities.at(i)->Active())
			projAct.push_back(m_entities.at(i));
		}


		

		if (playerBank != valueComp)
		{
			static_cast<CurrencyComponent*>(playerBank)->incrementValue(cash);
		}

		m_collidableEntities.at(index)->Active(false);

		cout << static_cast<CurrencyComponent*>(playerBank)->value() << endl;

	}
	/*auto tar = m_entities.at(j)->FindComponent("PC");
	tarX = static_cast<PositionComponent*>(tar)->getX();*/
}