#include "ProjectileSystem.h"



ProjectileSystem::ProjectileSystem(float xPos, float yPos, float speed, float orientation)
{
	int x = xPos;
	int y = yPos;
//	std::cout << x << std::endl;
	float m_orientation = orientation;
	float m_speed = speed;
	tempX, tempY = 0;
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

			// use SDL_Point instead
			tempX = sin(0.4);
			tempY = -cos(0.4);	

			velocityX = tempX * 8;
			velocityY = tempY * 8;

			x += velocityX;
			y += velocityY;

		//	std::cout << x << std::endl;

			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->X(x);
			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->Y(y);
		}
	}
}