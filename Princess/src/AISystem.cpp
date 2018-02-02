#include "AISystem.h"

void AISystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int pcKey = -1;
		int mcKey = -1;
		int seekKey = -1;
		int attackKey = -1;

		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				pcKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
			{
				mcKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "seek")
			{
				seekKey = j;
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "attack")
			{
				attackKey = j;
			}
		}

		if (seekKey >= 0 && pcKey >= 0 && mcKey >= 0)
		{
			if (attackKey >= 0)
			{
				if (static_cast<SeekComponent*>(m_entities.at(i)->GetComponents()->at(seekKey))->getDistanceToDestination() < static_cast<AttackComponent*>(m_entities.at(i)->GetComponents()->at(attackKey))->getRange())
				{
					attack(i, attackKey, mcKey);
				}
				else 
				{
					seek(i, pcKey, mcKey, seekKey);
				}
			}
			else
			{
				seek(i, pcKey, mcKey, seekKey);
			}
		}
	}
}

void AISystem::seek(int entityIndex, int pcKey, int mcKey, int seekKey)
{
	float x = static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getXDestination() - static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getX();
	float y = static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->getYDestination() - static_cast<PositionComponent*>(m_entities.at(entityIndex)->GetComponents()->at(pcKey))->getY();

	float dist = magnitude(x, y);

	static_cast<SeekComponent*>(m_entities.at(entityIndex)->GetComponents()->at(seekKey))->setDistanceToDestination(dist);

	if (dist > static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->getSpeed())
	{
		normalise(x, y);
		x *= static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->getSpeed();
		y *= static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->getSpeed();

		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(x);
		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(y);
	}
	else
	{
		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(0);
		static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(0);
	}
}

void AISystem::attack(int entityIndex, int attackKey, int mcKey)
{
	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setXVelocity(0);
	static_cast<MovementComponent*>(m_entities.at(entityIndex)->GetComponents()->at(mcKey))->setYVelocity(0);
}

void AISystem::normalise(float &x, float &y)
{
	float mag = magnitude(x, y);

	if (mag > 0)
	{
		x /= mag;
		y /= mag;
	}
}

float AISystem::magnitude(float x, float y)
{
	//return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)));
	return sqrt((x * x) + (y * y));
}