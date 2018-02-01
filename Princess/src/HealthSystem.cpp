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
					if (m_entities.at(i)->ID() == "Player")
					{
						UpdateHeartsStatus(m_entities.at(i));
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
		/*
		if (scKey >= 0)
		{

			if (m_entities.at(i)->ID() == "HeartsHealth")
			{
				//Draw Hearts Based On Health of Player
				//static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey))->Width();
				int scKey = -1;
				int hcKey = -1;
				for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
				{
					if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
					{
						scKey = j;
					}
					if (m_entities.at(i)->GetComponents()->at(j)->Type() == "HC")
					{
						hcKey = j;
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
						if (acKey >= 0 && scKey >= 0 && hcKey >=0)
						{
							if (static_cast<HeartComponent*>(m_entities.at(i)->GetComponents()->at(hcKey))->HeartType() == HeartTypes::HEALTH)
							{
								HeartComponent* hc = static_cast<HeartComponent*>(m_entities.at(i)->GetComponents()->at(hcKey));
								SpriteComponent* sc = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey));
								AttributesComponent* playerAc = static_cast<AttributesComponent*>(m_entities.at(j)->GetComponents()->at(acKey));
								if (hc->Index() < hc->HeartList()->size())
								{
									int numHearts = (playerAc->MaxHealth() / 2);
									int numFullHearts = (playerAc->Health() / 2);
									if (hc->Index() == (numFullHearts + 1))
									{
										if (hc->State() != HeartState::HALF)
										{
											hc->State(HeartState::HALF);
											//Change Sprite Sheet Position
										}
									}
									else if (hc->Index() > (numFullHearts + 1))
									{
										if (hc->State() != HeartState::EMPTY)
										{
											hc->State(HeartState::EMPTY);
											//Change Sprite Sheet Position
										}
									}
									else
									{
										if (hc->State() != HeartState::FULL)
										{
											hc->State(HeartState::FULL);
											//Change Sprite Sheet Position
										}
									}
								}


							}
						}
					}
				}
				
			}
		}
		*/
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


void HealthSystem::UpdateHeartsStatus(Entity* player)
{
	int acKey = -1;
	for (int k = 0; k < player->GetComponents()->size(); k++)
	{
		if (player->GetComponents()->at(k)->Type() == "AC")
		{
			acKey = k;
		}
	}
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == "Hearts")
		{
			int scKey = -1;
			int hcKey = -1;
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					scKey = j;
				}
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "HC")
				{
					hcKey = j;
				}
			}
			if (acKey >= 0 && scKey >= 0 && hcKey >= 0)
			{
				if (static_cast<HeartComponent*>(m_entities.at(i)->GetComponents()->at(hcKey))->HeartType() == HeartTypes::HEALTH)
				{
					HeartComponent* hc = static_cast<HeartComponent*>(m_entities.at(i)->GetComponents()->at(hcKey));
					SpriteComponent* sc = static_cast<SpriteComponent*>(m_entities.at(i)->GetComponents()->at(scKey));
					AttributesComponent* playerAc = static_cast<AttributesComponent*>(player->GetComponents()->at(acKey));
					if (hc->Index() < hc->HeartList()->size())
					{
						int numHearts = (playerAc->MaxHealth() / 2);
						int numFullHearts = (playerAc->Health() / 2);
						if (hc->Index() == (numFullHearts))
						{
							if (hc->State() != HeartState::HALF)
							{
								hc->State(HeartState::HALF);
								sc->Frame(1);
							}
						}
						else if (hc->Index() > numFullHearts)
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

void HealthSystem::UpdateMaxHearts()
{
	for (int a = 0; a < m_entities.size(); a++)
	{
		if (m_entities.at(a)->ID() == "Player")
		{
			int acKey = -1;
			for (int k = 0; k < m_entities.at(a)->GetComponents()->size(); k++)
			{
				if (m_entities.at(a)->GetComponents()->at(k)->Type() == "AC")
				{
					acKey = k;
				}
			}

			for (int i = 0; i < m_entities.size(); i++)
			{
				if (m_entities.at(i)->ID() == "Hearts")
				{
					int hcKey = -1;
					for (int k = 0; k < m_entities.at(a)->GetComponents()->size(); k++)
					{
						if (m_entities.at(a)->GetComponents()->at(k)->Type() == "HC")
						{
							hcKey = k;
						}
					}
					if (hcKey >= 0 && acKey >=0)
					{
						HeartComponent* hc = static_cast<HeartComponent*>(m_entities.at(i)->GetComponents()->at(hcKey));
						AttributesComponent* ac = static_cast<AttributesComponent*>(m_entities.at(a)->GetComponents()->at(acKey));
						int numFullHearts = (ac->Health() / 2);
						for (int i = numFullHearts; numFullHearts < hc->HeartList()->size(); i++)
						{
							Entity * heart = new Entity("Hearts");
							heart->AddComponent(new PositionComponent());

							if (i >= 10)
							{
								static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->X(20 * (i - 10));
								static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->Y(20 + 20);
							}
							else
							{
								static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->X(20 * i);
								static_cast<PositionComponent*>((heart)->GetComponents()->at(0))->Y(20);
							}
							heart->AddComponent(new SpriteComponent("HeartsSheet", 3, 0, 0, 16, 16, 0));
							heart->AddComponent(new HeartComponent(hc->HeartList()));
							hc->HeartList()->push_back(heart);
							static_cast<HeartComponent*>((heart)->GetComponents()->at(2))->Index(hc->HeartList()->size() - 1);
						}
					}

				}
			}



		}
	}
}

