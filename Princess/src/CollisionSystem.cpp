#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{

}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == "Player" || m_entities.at(i)->ID() == "Projectile")
		{


			int pcKeyOne = -1;
			int ccKeyOne = -1;
			int pcKeyTwo = -1;
			int ccKeyTwo = -1;
			//std::string projectileCheck = "Projectile";
			//std::string playerCheck = "Player";

			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					pcKeyOne = j;
				}
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					ccKeyOne = j;
				}
			}

			for (int k = 0; k < m_entities.size(); k++)
			{
				for (int j = 0; j < m_entities.at(k)->GetComponents()->size(); j++)
				{
					if (m_entities.at(k)->GetComponents()->at(j)->Type() == "PC")
					{
						pcKeyTwo = j;
					}
					if (m_entities.at(k)->GetComponents()->at(j)->Type() == "SC")
					{
						ccKeyTwo = j;
					}
				}

				int x1 = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKeyOne))->getPosition().x;
				int y1 = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKeyOne))->getPosition().y;

				int x2 = static_cast<PositionComponent*>(m_entities.at(k)->GetComponents()->at(pcKeyTwo))->getPosition().x;
				int y2 = static_cast<PositionComponent*>(m_entities.at(k)->GetComponents()->at(pcKeyTwo))->getPosition().y;


				int w1 = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ccKeyOne))->GetRect().w;
				int h1 = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ccKeyOne))->GetRect().h;

				int w2 = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ccKeyTwo))->GetRect().w;
				int h2 = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(ccKeyTwo))->GetRect().h;


				// BASIC COLLISION DETECTION
				if (x1 != x2 || y1 != y2)
				{
					if ((x1 >= x2) && (x1 <= (x2 + w2))
						&& (y1 >= y2 && y1 <= (y2 + w2)))
					{
						//std::cout << "COLLISION!!!" << std::endl;
					}
				}


				//if (x1 != x2 || y1 != y2)
				//{
				//	if (x1 < (x2))
				//	{
				//		if (x1 + w1 >= x2)
				//		{
				//			std::cout << "FROM THE RIGHT" << std::endl;
				//			int temp = x1 - 2;
				//			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKeyOne))->setX(temp);
				//		}
				//	}
				//	if (x1 > x2)
				//	{
				//		if (x1 <= x2 + w2)
				//		{
				//			std::cout << "FROM THE RIGHT" << std::endl;
				//			int temp = x1 + 2;
				//			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKeyOne))->setX(temp);
				//		}
				//	}	
				//	/*}*/
				//}

				//std::cout << "x1 " << x1 << std::endl;
				//std::cout << "y1 " << y1 << std::endl;
				//std::cout << "x2 " << x2 << std::endl;
				//std::cout << "y2 " << y2 << std::endl;

			}
		}
	}
}

