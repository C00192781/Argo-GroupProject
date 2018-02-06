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
		int rectangleKey = -1; // POSITION
		int scKey = -1;
		int pjKey = -1; // 
		int mcKey = -1;
		std::string check = "Projectile";

		std::string playerCheck = "Player";

		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "rectangle" && m_entities.at(i)->ID() == check)
			{
				rectangleKey = j;
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

		if (pjKey >= 0 && rectangleKey >= 0 && mcKey >= 0)
		{
			//float tempAngle = 90;

			float m_orientation = static_cast<ProjectileComponent*>(m_entities.at(i)->GetComponents()->at(pjKey))->getOrientation();
			Vector2f v;
			v = VelocityHandler(m_orientation);

			float timePressed = static_cast<ProjectileComponent*>(m_entities.at(i)->GetComponents()->at(pjKey))->getButtonPressTime();
			float maxSpeed = static_cast<ProjectileComponent*>(m_entities.at(i)->GetComponents()->at(pjKey))->getMaxSpeed();

			float speed = CalculateSpeed(timePressed, maxSpeed);

			Vector2f velocity = MovementHandler(v.X, v.Y, speed);

			// assign velocity
			static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setXVeclocity(velocity.X);
			static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setYVeclocity(velocity.Y);	
		}
	}
}

Vector2f ProjectileSystem::VelocityHandler(float orientation)
{
	float TX = sin(orientation);
	float TY = -cos(orientation);

	return Vector2f{ TX, TY };
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
	float press = std::ceil(buttonPressTime);
	float modifier = press / maxHoldTime;
	if (modifier >= 1)
	{
		modifier = 1;
	}
	float speed = modifier * maxSpeed;
	return speed; 
}


std::vector<Entity*>* ProjectileSystem::getEntities()
{
	return &m_entities;
}
