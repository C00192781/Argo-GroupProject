#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{

}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::Update()
{
	std::string projectileCheck = "Projectile";
	std::string playerCheck = "Player";

	int pcKey = -1;
	int scKey = -1;


	std::vector<int> posIndex;
	std::vector<int> spriteIndex;
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == "Projectile" && m_entities.at(i)->ID() != "Player")
		{
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC" && m_entities.at(i)->ID() == projectileCheck)
				{
					posIndex.push_back(j);
				}
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC" && m_entities.at(i)->ID() == projectileCheck)
				{
					spriteIndex.push_back(j);
				}
			}

		}


		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{

			if (m_entities.at(i)->ID() == playerCheck && m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				if (static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j))->getPosition().x > -10000)
				{
					x1 = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j))->getPosition().x;
				}
				if (static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j))->getPosition().y > -10000)
				{
					y1 = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j))->getPosition().y;
				}
			}
			if (m_entities.at(i)->ID() == playerCheck && m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
			{
				if (static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->GetRect().w > -10000)
				{
					w1 = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->GetRect().w;
				}
				if (static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->GetRect().h > -10000)
				{
					h1 = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->GetRect().h;
				}
			}
		}
		for (int p = 0; p < posIndex.size(); p++)
		{
		
			int x2 = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(posIndex[p]))->getPosition().x;
			int y2 = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(posIndex[p]))->getPosition().y;


			int w2 = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(spriteIndex[p]))->GetRect().w;
			int h2 = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(spriteIndex[p]))->GetRect().h;

			if (x1 != x2 && y1 != y2)
			{
				if ((x1 >= x2) && (x1 <= (x2 + w2))
					&& (y1 >= y2 && y1 <= (y2 + w2)))
				{
					//std::cout << "COLLISION!!!" << std::endl;

					collision = true;					
				}
				else
				{
					collision = false;
				}
			}
		}
		if (collision == true)
		{
			if (m_entities.at(i)->ID() == playerCheck)
			{
				AttributesComponent * ac = nullptr;
				int acKey = -1;
				for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
				{
					if (m_entities.at(i)->GetComponents()->at(j)->Type() == "AC")
					{
						acKey = j;
						ac = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(j));
					}
				}
				if (acKey >= 0 && ac != nullptr)
				{
					ac->Modifers()->push_back(Modifer(ModiferTypes::DAMAGE, 10, 0));
				}
			}
		}
	}
}


