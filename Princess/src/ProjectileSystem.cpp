#include "ProjectileSystem.h"

ProjectileSystem::ProjectileSystem(float xPos, float yPos, float speed, float orientation)
{
	x = xPos;
	y = yPos;
	m_orientation = orientation;
	m_speed = speed;
}


ProjectileSystem::~ProjectileSystem()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
		m_entities.erase(m_entities.begin() + i);
		m_entities.shrink_to_fit();
	}
}

void ProjectileSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int pcKey = -1;
		int scKey = -1;
		int pjKey = -1;
		std::string check = "Projectile";

		std::string playerCheck = "Player";

		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC" && m_entities.at(i)->ID() == check)
			{
				pjKey = j;
			}
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC" && m_entities.at(i)->ID() == playerCheck)
			{
				pcKey = j;
			}
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC" && m_entities.at(i)->ID() == playerCheck)
			{
				scKey = j;
			}
		}


		if (pcKey >= 0 && scKey >= 0)
		{

			int playerWidth = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Width();
			int playerHeight = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Height();

			playerX = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X();
			playerY = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Y();


			//static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X(44);

			// EXTREMELY BASIC COLLISION DETECTION
			if ((x >= playerX) && (x <= (playerX + playerWidth))
				&& (y >= playerY && y <= (playerY + playerHeight)))
			{
				std::cout << "COLLISION!!!" << std::endl;
			}


		}


		if (pjKey >= 0)
		{
			//float tempAngle = 90;


			velocityHandler(m_orientation);
			movementHandler(m_speed);

			// assign position
			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pjKey))->X(x);
			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pjKey))->Y(y);
		}
	}
}

void ProjectileSystem::velocityHandler(float orientation)
{
	float TX = sin(orientation);
	float TY = -cos(orientation);
	velocityX = TX;
	velocityY = TY;
}


void ProjectileSystem::movementHandler(float speed)
{
	velocityX *= m_speed;
	velocityY *= m_speed;

	x += velocityX;
	/*std::cout << x << std::endl;*/
	y += velocityY;
}
