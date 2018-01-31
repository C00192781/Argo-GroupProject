#include "HealthSystem.h"

HealthSystem::HealthSystem()
{

}

HealthSystem::~HealthSystem()
{

}

void HealthSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int acKey = -1;
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
			{
				acKey = j;
			}
		}
		if (acKey >= 0)
		{
			std::list<Modifer> * modifiers = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Modifers();
			for(std::list<Modifer>::iterator it = modifiers->begin(); it != modifiers->end(); ++it)
			{
				if ((*it).type == ModiferTypes::DAMAGE)
				{
					int damageCaused = (*it).amount;
					int armour = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Armour();
					int health = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Health();
					DamageEntity(damageCaused, armour, health);
				}
			}
			//Remove Modifiers whose duration has ended
			for (std::list<Modifer>::iterator it = modifiers->begin(); it != modifiers->end(); ++it)
			{
				if ((*it).duration <= 0)
				{
					it=modifiers->erase(it);
				}
			}
		}
	}
}

void HealthSystem::DamageEntity(int damageCaused, int armour, int health)
{
	armour = armour - damageCaused;
	if (armour <= 0)
	{
		health = health + armour;
		armour = 0;
	}
	if (health < 0)
	{
		//Dies
	}
}

