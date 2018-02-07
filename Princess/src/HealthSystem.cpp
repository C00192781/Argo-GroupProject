#include "HealthSystem.h"

HealthSystem::HealthSystem()
{
	timer = 0;
}

HealthSystem::~HealthSystem()
{

}

void HealthSystem::Update(float deltaTime)
{

		for (int i = 0; i < m_entities.size(); i++)
		{
			int acKey = -1;
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "AC")
				{
					acKey = j;
				}
			}
			if (acKey >= 0)
			{
				std::list<Modifer> * modifiers = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Modifers();
				if (modifiers->size() != 0)
				{
					//Goes through all the modifiers the Attributes Component has
					for (std::list<Modifer>::iterator it = modifiers->begin(); it != modifiers->end(); ++it)
					{
						if (timer > 1)
						{
							if ((*it).m_type == ModiferTypes::BURNING)
							{
								int damageCaused = (*it).m_amount;
								int armour = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Armour();
								int health = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Health();
								DamageEntity(damageCaused, armour, health);
								static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Armour(armour);
								static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Health(health);
							}

							(*it).m_duration = (*it).m_duration - 1;
							timer = 0;
						}
						else
						{
							timer += deltaTime;
						}
						//Applies Damage to the armour and health
						if ((*it).m_type == ModiferTypes::DAMAGE)
						{
							int damageCaused = (*it).m_amount;
							int armour = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Armour();
							int health = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Health();
							DamageEntity(damageCaused, armour, health);
							static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Armour(armour);
							static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->Health(health);
						}
						//Updates Health and Armour UI
						if (m_entities.at(i)->ID() == "Player")
						{
							UpdateHeartsUIStatus(m_entities.at(i), m_entities.at(i));
							UpdateArmourUIStatus(m_entities.at(i), m_entities.at(i));
						}

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

void HealthSystem::UpdateHeartsUIStatus(Entity * HeartManager, Entity* player)
{
	int acKey = -1;
	for (int k = 0; k < player->GetComponents()->size(); k++)
	{
		if (player->GetComponents()->at(k)->Type() == "AC")
		{
			acKey = k;
		}
	}
	int hmcKey = -1;
	for (int j = 0; j < HeartManager->GetComponents()->size(); j++)
	{
		if (HeartManager->GetComponents()->at(j)->Type() == "HMC")
		{
			hmcKey = j;
			if (static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartType() == HeartTypes::HEALTH)
			{
				break;
			}
			else
			{
				hmcKey = -1;
			}
		}

	}
	if (acKey >= 0 && hmcKey >= 0)
	{
		if (static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartType() == HeartTypes::HEALTH)
		{
			std::vector<Entity*>* heartVector = static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartsVector();
			for (int i = 0; i < heartVector->size(); i++)
			{
				int scKey = -1;
				int hcKey = -1;
				for (int j = 0; j < heartVector->at(i)->GetComponents()->size(); j++)
				{
					if (heartVector->at(i)->GetComponents()->at(j)->Type() == "SC")
					{
						scKey = j;
					}
					if (heartVector->at(i)->GetComponents()->at(j)->Type() == "HC")
					{
						hcKey = j;
					}
				}
				if (scKey >= 0 && hcKey >= 0)
				{
					SpriteComponent* sc = static_cast<SpriteComponent*>(heartVector->at(i)->GetComponents()->at(scKey));
					HeartComponent* hc = static_cast<HeartComponent*>(heartVector->at(i)->GetComponents()->at(hcKey));

					AttributesComponent* playerAc = static_cast<AttributesComponent*>(player->GetComponents()->at(acKey));
					if (hc->Index() < hc->HeartList()->size())
					{
						int numHearts = (playerAc->MaxHealth() / 2.0f);
						float numFullHearts = (playerAc->Health() / 2.0f);

						if (hc->Index() >= (numFullHearts - 0.5f) && hc->Index() < (numFullHearts) && hc->Index() != numFullHearts)
						{
							if (hc->State() != HeartState::HALF)
							{
								hc->State(HeartState::HALF);
								sc->Frame(1);
							}
						}
						else if (hc->Index() >= numFullHearts)
						{
							if (hc->State() != HeartState::EMPTY)
							{
								hc->State(HeartState::EMPTY);
								sc->Frame(2);
							}
						}
						else
						{
							if (hc->State() != HeartState::FULL)
							{
								hc->State(HeartState::FULL);
								sc->Frame(0);
							}
						}
					}
					else
					{
						std::cout << "ERROR INDEX LARGER THAN LIST SIZE" << std::endl;
					}			
				}
			}
		}
		else
		{
			std::cout << "ERROR WRONG HEART TYPE" << std::endl;
		}
	}
}

void HealthSystem::UpdateMaxArmourUI(Entity * HeartManager, Entity* player)
{
	int acKey = -1;
	for (int k = 0; k < player->GetComponents()->size(); k++)
	{
		if (player->GetComponents()->at(k)->Type() == "AC")
		{
			acKey = k;
		}
	}
	int hmcKey = -1;
	for (int j = 0; j < HeartManager->GetComponents()->size(); j++)
	{
		if (HeartManager->GetComponents()->at(j)->Type() == "HMC")
		{
			hmcKey = j;
			if (static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartType() == HeartTypes::ARMOUR)
			{
				break;
			}
			else
			{
				hmcKey = -1;
			}
		}
	}
	if (hmcKey >= 0 && acKey >= 0)
	{
		if (static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartType() == HeartTypes::ARMOUR)
		{
			std::vector<Entity*>* heartVector = static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartsVector();
			AttributesComponent* ac = static_cast<AttributesComponent*>(player->GetComponents()->at(acKey));
			int numFullHearts = heartVector->size();

			for (int i = numFullHearts; i < (ac->MaxArmour() / 2); i++)
			{
				Entity * armour = new Entity("ArmourDisplay");
				armour->AddComponent(new PositionComponent());

				if (i >= 10)
				{
					static_cast<PositionComponent*>((armour)->GetComponents()->at(0))->setX(60 * (i - 10));
					static_cast<PositionComponent*>((armour)->GetComponents()->at(0))->setY(170 + 20);
				}
				else
				{
					static_cast<PositionComponent*>((armour)->GetComponents()->at(0))->setX(60 * i);
					static_cast<PositionComponent*>((armour)->GetComponents()->at(0))->setY(140);
				}
				armour->AddComponent(new SpriteComponent("ArmourSheet", 2, 3, 0, 0, 16, 16, 0));
				static_cast<SpriteComponent*>((armour)->GetComponents()->at(1))->IsAnimating(false);
				armour->AddComponent(new HeartComponent(heartVector));
				heartVector->push_back(armour);
				static_cast<HeartComponent*>((armour)->GetComponents()->at(2))->Index(heartVector->size() - 1);
				armour->Transient(true);
				m_entities.push_back(armour);
			}
			UpdateArmourUIStatus(HeartManager, player);
		}

	}
}

void HealthSystem::UpdateArmourUIStatus(Entity * HeartManager, Entity* player)
{
	int acKey = -1;
	for (int k = 0; k < player->GetComponents()->size(); k++)
	{
		if (player->GetComponents()->at(k)->Type() == "AC")
		{
			acKey = k;
		}
	}
	int hmcKey = -1;
	for (int j = 0; j < HeartManager->GetComponents()->size(); j++)
	{
		if (HeartManager->GetComponents()->at(j)->Type() == "HMC")
		{
			hmcKey = j;
			if (static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartType() == HeartTypes::ARMOUR)
			{
				break;
			}
			else
			{
				hmcKey = -1;
			}
		}
	}
	if (hmcKey >= 0 && acKey >= 0)
	{
		if (static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartType() == HeartTypes::ARMOUR)
		{
			std::vector<Entity*>* heartVector = static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartsVector();
			for (int i = 0; i < heartVector->size(); i++)
			{
				int scKey = -1;
				int hcKey = -1;
				for (int j = 0; j < heartVector->at(i)->GetComponents()->size(); j++)
				{
					if (heartVector->at(i)->GetComponents()->at(j)->Type() == "SC")
					{
						scKey = j;
					}
					if (heartVector->at(i)->GetComponents()->at(j)->Type() == "HC")
					{
						hcKey = j;
					}
				}
				if (scKey >= 0 && hcKey >= 0)
				{
					SpriteComponent* sc = static_cast<SpriteComponent*>(heartVector->at(i)->GetComponents()->at(scKey));
					HeartComponent* hc = static_cast<HeartComponent*>(heartVector->at(i)->GetComponents()->at(hcKey));

					AttributesComponent* playerAc = static_cast<AttributesComponent*>(player->GetComponents()->at(acKey));
					if (hc->Index() < hc->HeartList()->size())
					{
						int numHearts = (playerAc->MaxArmour() / 2.0f);
						float numFullHearts = ((float)playerAc->Armour() / 2.0f);
						if (hc->Index() >= (numFullHearts - 0.5f) && hc->Index() < (numFullHearts) && hc->Index() != numFullHearts)
						{
							if (hc->State() != HeartState::HALF)
							{
								hc->State(HeartState::HALF);
								sc->Frame(1);
							}
						}
						else if (hc->Index() >= numFullHearts)
						{
							if (hc->State() != HeartState::EMPTY)
							{
								hc->State(HeartState::EMPTY);
								sc->Frame(2);
							}
						}
						else
						{
							if (hc->State() != HeartState::FULL)
							{
								hc->State(HeartState::FULL);
								sc->Frame(0);
							}
						}
					}
					else
					{
						std::cout << "ERROR INDEX LARGER THAN LIST SIZE" << std::endl;
					}
				}
			}
		}
	}
}

void HealthSystem::UpdateMaxHeartsUI(Entity * HeartManager, Entity* player)
{
	int acKey = -1;
	for (int k = 0; k < player->GetComponents()->size(); k++)
	{
		if (player->GetComponents()->at(k)->Type() == "AC")
		{
			acKey = k;
		}
	}
	int hmcKey = -1;
	for (int j = 0; j < HeartManager->GetComponents()->size(); j++)
	{
		if (HeartManager->GetComponents()->at(j)->Type() == "HMC")
		{
			hmcKey = j;
			if (static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartType() == HeartTypes::HEALTH)
			{
				break;
			}
			else
			{
				hmcKey = -1;
			}
		}
	}
	if (hmcKey >= 0 && acKey >= 0)
	{
		if (static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartType() == HeartTypes::HEALTH)
		{
			std::vector<Entity*>* heartVector = static_cast<HeartManagerComponent*>(HeartManager->GetComponents()->at(hmcKey))->HeartsVector();
			AttributesComponent* ac = static_cast<AttributesComponent*>(player->GetComponents()->at(acKey));
			int numFullHearts = heartVector->size();
			for (int i = numFullHearts; i < (ac->MaxHealth() / 2); i++)
			{
				Entity * heart = new Entity("Hearts");
				heart->AddComponent(new PositionComponent());

				if (i >= 10)
				{
					static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->setX(60 * (i - 10));
					static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->setY(20 + 60);
				}
				else
				{
					static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->setX(60 * i);
					static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->setY(20);
				}
				heart->AddComponent(new SpriteComponent("HeartsSheet", 2, 3, 0, 0, 16, 16, 0));
				static_cast<SpriteComponent*>((heart)->GetComponents()->at(1))->IsAnimating(false);
				heart->AddComponent(new HeartComponent(heartVector));
				heartVector->push_back(heart);
				static_cast<HeartComponent*>((heart)->GetComponents()->at(2))->Index(heartVector->size() - 1);
				heart->Transient(true);
				m_entities.push_back(heart);
			}
			UpdateHeartsUIStatus(HeartManager, player);
		}
	}
}

