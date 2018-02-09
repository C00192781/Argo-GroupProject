#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{

}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::Update()
{
	float playerPosX = 0.0f;
	float playerPosY = 0.0f;
	float projectilePosX = 0.0f;
	float projectilePosY = 0.0f;
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() != "Hearts" && m_entities.at(i)->ID() != "ArmourDisplay")
		{
			int pcKeyOne = -1;
			int ccKeyOne = -1;
			int pcKeyTwo = -1;
			int ccKeyTwo = -1;
			std::string projectileCheck = "Projectile";
			std::string playerCheck = "Player";

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
						std::cout << "COLLISION!!!" << std::endl;
					}
				}

			}
		}
	}
}

