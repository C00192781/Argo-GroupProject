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
		int scKey = -1;
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "AC")
			{
				acKey = j;
			}
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
			{
				scKey = j;
			}
		}
		if (acKey >= 0)
		{
			std::list<Modifer> * modifiers = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Modifers();
			if (modifiers->size() != 0)
			{
				for (std::list<Modifer>::iterator it = modifiers->begin(); it != modifiers->end(); ++it)
				{
					if ((*it).m_type == ModiferTypes::DAMAGE)
					{
						int damageCaused = (*it).m_amount;
						int armour = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Armour();
						int health = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Health();
						DamageEntity(damageCaused, armour, health);
						static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Armour(armour);
						static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Health(health);
					}
					(*it).m_duration = (*it).m_duration - 1;
				}
				//Remove Modifiers whose duration has ended
				for (std::list<Modifer>::iterator it = modifiers->begin(); it != modifiers->end();)
				{
					if ((*it).m_duration <= 0)
					{
						it = modifiers->erase(it);
					}
					else
					{
						++it;
					}

				}
			}
		}
		if (scKey >= 0)
		{
			if (m_entities.at(i)->ID() == "HeartsHealth")
			{
				//Draw Hearts Based On Health of Player
				//static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Width();
				int scKey = -1;
				for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
				{
					if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
					{
						scKey = j;
					}
				}
				for (int j = 0; j < m_entities.size(); j++)
				{
					if (m_entities.at(j)->ID() == "Player")
					{
						int acKey = -1;
						for (int k = 0; k < m_entities.at(j)->GetComponents()->size(); k++)
						{
							if (m_entities.at(j)->GetComponents()->at(k)->Type() == "AC")
							{
								acKey = k;
							}
						}
						if (acKey >= 0 && scKey >= 0)
						{
							int health = static_cast<AttributesComponent*>(m_entities.at(j)->GetComponents()->at(acKey))->Health();
							int maxHealth = static_cast<AttributesComponent*>(m_entities.at(j)->GetComponents()->at(acKey))->MaxHealth();
							int heartsWidth = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Width();
							if (health != maxHealth && heartsWidth != 80)
							{
								heartsWidth = heartsWidth*(1 / ((float)health / (float)maxHealth));
							}
							heartsWidth = heartsWidth*((float)health / (float)maxHealth);
							static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Width(heartsWidth);
						}

					}
				}
			}
		}
	}
}

void HealthSystem::DamageEntity(int& damageCaused, int& armour, int& health)
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

