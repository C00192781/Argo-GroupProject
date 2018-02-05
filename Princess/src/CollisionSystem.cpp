#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{

}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::Update()
{

	int pcKeyOne = -1;
	int ccKeyOne = -1;
	std::string projectileCheck = "Projectile";
	std::string playerCheck = "Player";


	std::vector<int> posIndex;
	std::vector<int> spriteIndex;
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == "Projectile" || m_entities.at(i)->ID() != "Player")
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




		//	int x1 = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKeyOne))->getPosition().x;
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{

			if (m_entities.at(i)->ID() == playerCheck && m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				if (static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j))->getPosition().x > -22222)
				{
					x1 = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j))->getPosition().x;
				}
				if (static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j))->getPosition().y > -22222)
				{
					y1 = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(j))->getPosition().y;
				}

				/*std::cout << "x1 " << x1 << std::endl;*/

			}
			if (m_entities.at(i)->ID() == playerCheck && m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
			{
				if (static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->GetRect().w > -22222)
				{
					w1 = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->GetRect().w;
				}
				if (static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->GetRect().h > -22222)
				{
					h1 = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(j))->GetRect().h;
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
						std::cout << "COLLISION!!!" << std::endl;
					}
				}
			}
		}
	}
	
}


