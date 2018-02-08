#include "ProjectileSystem.h"

ProjectileSystem::ProjectileSystem()
{

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
	//std::cout << m_entities.size() << std::endl;
	for (int i = 0; i < m_entities.size(); i++)
	{
		int pcKey = -1; // POSITION
		int scKey = -1;
		int pjKey = -1; // 
		int mcKey = -1;

		//if (m_entities.at(i)->Active())
		//{
		//	std::cout << "ddidy" << std::endl;
		//}
		//
		std::string check = "Projectile";

		std::string playerCheck = "Player";

		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC" && m_entities.at(i)->ID() == check)
			{
				pcKey = j;
			}
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PJ" && m_entities.at(i)->ID() == check)
			{
				pjKey = j;
			}
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement" && m_entities.at(i)->ID() == check)
			{
				mcKey = j;
			}
		}

		if (pjKey >= 0 && pcKey >= 0 && mcKey >= 0)
		{
			//float tempAngle = 90;
			bool alive = static_cast<ProjectileComponent*>(m_entities.at(i)->GetComponents()->at(pjKey))->getAliveStatus();
			if (alive == true)
			{
				m_entities.at(i)->Active(true);
				
				float m_orientation = static_cast<ProjectileComponent*>(m_entities.at(i)->GetComponents()->at(pjKey))->getOrientation();
				Vector2f v;
				v = VelocityHandler(m_orientation);

				float timePressed = static_cast<ProjectileComponent*>(m_entities.at(i)->GetComponents()->at(pjKey))->getButtonPressTime();
				float maxSpeed = static_cast<ProjectileComponent*>(m_entities.at(i)->GetComponents()->at(pjKey))->getMaxSpeed();

				float speed = CalculateSpeed(timePressed, maxSpeed);

				Vector2f velocity = MovementHandler(v.X, v.Y, speed);

				// assign velocity
				static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setXVelocity(velocity.X);
				static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setYVelocity(velocity.Y);
			}
			if (alive == false)
			{
				m_entities.at(i)->Active(false);
				// assign velocity
				static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setXVelocity(0);
				static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setYVelocity(0);
			}
		}
	}
}

Vector2f ProjectileSystem::VelocityHandler(float orientation)
{
	float TX = sin(orientation);
	float TY = -cos(orientation);

	return Vector2f{ TX, TY };
}

std::vector<Entity*>* ProjectileSystem::getEntities()
{
	return &m_entities;
}

Vector2f ProjectileSystem::MovementHandler(float velocityX, float velocityY, float speed)
{
	float velX = velocityX;
	float velY = velocityY;

	velX *= speed;
	velY *= speed;

	return Vector2f{ velX, velY };
}

/// <summary>
///  We use the amount of time that player has pressed the shooting button 
///  to calculate how fast the projectile will travel
/// </summary>

float ProjectileSystem::CalculateSpeed(float buttonPressTime, float maxSpeed)
{
	// may round up values
	float press = buttonPressTime;
	if (press < 1)
	{
		press = std::ceil(buttonPressTime);
	}
	float modifier = press / maxHoldTime;
	if (modifier >= 1)
	{
		modifier = 1;
	}
	float speed = modifier * maxSpeed;
	//std::cout << speed << std::endl;
	return speed;
}



