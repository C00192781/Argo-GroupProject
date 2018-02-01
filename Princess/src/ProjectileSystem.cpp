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
	
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				pcKey = j;
			}
		}

		if (pcKey >= 0)
		{
			//float tempAngle = 90;

			velocityHandler(m_orientation);
			movementHandler(m_speed);

			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X(x);
			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Y(y);
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
	y += velocityY;
}
