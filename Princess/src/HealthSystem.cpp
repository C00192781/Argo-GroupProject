#include "HealthSystem.h"

HealthSystem::HealthSystem(StateManager * sm)
{
	timer = 0;
	m_entities.push_back(new Entity("Null"));
	delete m_entities.back();
	m_entities.clear();
	m_stateManager = sm;
}

HealthSystem::~HealthSystem()
{

}

void HealthSystem::LoadComponent()
{
	for (int j = 0; j < m_entities.back()->GetComponents()->size(); j++)
	{
		if (m_entities.back()->GetComponents()->at(j)->Type() == "attribute")
		{
			m_attributeComponents.push_back(static_cast<AttributesComponent*>(m_entities.back()->GetComponents()->at(j)));
			break;
		}
	}
}

void HealthSystem::UnloadComponent(int x)
{
	//m_positionComponent.erase(m_positionComponent.begin() + x);
	//m_spriteComponent.erase(m_spriteComponent.begin() + x);
	//m_positionComponent.shrink_to_fit();
	//m_spriteComponent.shrink_to_fit();
}

void HealthSystem::DeactivateHearts()
{
	for (int i = 0; i < m_player1Hearts.size(); i++)
	{
		m_player1Hearts.at(i)->Active(false);
	}
	for (int i = 0; i < m_player2Hearts.size(); i++)
	{
		m_player2Hearts.at(i)->Active(false);
	}
	for (int i = 0; i < m_player3Hearts.size(); i++)
	{
		m_player3Hearts.at(i)->Active(false);
	}
	for (int i = 0; i < m_player4Hearts.size(); i++)
	{
		m_player4Hearts.at(i)->Active(false);
	}
	
}

void HealthSystem::ActivateHearts()
{
	for (int i = 0; i < m_player1Hearts.size(); i++)
	{
		m_player1Hearts.at(i)->Active(true);
	}
	for (int i = 0; i < m_player2Hearts.size(); i++)
	{
		m_player2Hearts.at(i)->Active(true);
	}
	for (int i = 0; i < m_player3Hearts.size(); i++)
	{
		m_player3Hearts.at(i)->Active(true);
	}
	for (int i = 0; i < m_player4Hearts.size(); i++)
	{
		m_player4Hearts.at(i)->Active(true);
	}

}

void HealthSystem::HealAllEntities()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->FindComponent("attribute") != nullptr)
		{
			AttributesComponent *  ac = static_cast<AttributesComponent*>(m_entities.at(i)->FindComponent("attribute"));
			ac->Health(ac->MaxHealth());
			ac->Armour(ac->MaxArmour());
		}
	}
}

void HealthSystem::AddEntity(Entity * e, std::string tag)
{
	if (tag == "PH1")
	{
		m_player1Hearts.push_back(e);
	}
	else if (tag == "PH2")
	{
		m_player2Hearts.push_back(e);
	}
	else if (tag == "PH3")
	{
		m_player3Hearts.push_back(e);
	}
	else if (tag == "PH4")
	{
		m_player4Hearts.push_back(e);
	}
	else
	{
		m_entities.push_back(e);
		LoadComponent();
	}
}

void HealthSystem::Update(float deltaTime)
{
	if (m_entities.size() > 0) { PlayerOneUpdate(); }
	if (m_entities.size() > 1) { PlayerTwoUpdate(); }
	if (m_entities.size() > 2) { PlayerThreeUpdate(); }
	if (m_entities.size() > 3) { PlayerFourUpdate(); }
	
	CheckIfAllDead();
}

void HealthSystem::PlayerOneUpdate()
{
	int healthHolder = m_attributeComponents.at(0)->Health() / 2;
	int maxHealthHolder = m_attributeComponents.at(0)->MaxHealth() / 2;
	int armorHolder = m_attributeComponents.at(0)->Armour() / 2;
	int maxArmorHolder = m_attributeComponents.at(0)->MaxArmour() / 2;
	for (int i = 0; i < 12; i++)
	{
		bool spriteGot = false;
		bool positionGot = false;
		if (i < maxHealthHolder)
		{
			m_player1Hearts.at(i)->Active(true);
			for (int j = 0; j < m_player1Hearts.at(i)->GetComponents()->size(); j++)
			{
				if (positionGot && spriteGot)
				{
					break;
				}
				else if (m_player1Hearts.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					if (i < healthHolder)
					{
						static_cast<SpriteComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->Direction(0);
					}
					else if ((float)i + 0.5 == (float)m_attributeComponents.at(0)->Health() / 2)
					{
						static_cast<SpriteComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->Direction(1);
					}
					else
					{
						static_cast<SpriteComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->Direction(2);
					}
					spriteGot = true;
				}
				else if (m_player1Hearts.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					if (i < 6)
					{
						static_cast<PositionComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->setX((i * 4) * 3);
						static_cast<PositionComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->setY(0);
					}
					else
					{
						static_cast<PositionComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->setX(((i - 6) * 4) * 3);
						static_cast<PositionComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->setY(4 * 3);
					}
					positionGot = true;
				}
			}
		}
		else
		{
			m_player1Hearts.at(i)->Active(false);
		}
	}
	for (int i = 12; i < 18; i++)
	{
		bool spriteGot = false;
		bool positionGot = false;
		if (i < 12 + maxArmorHolder)
		{
			m_player1Hearts.at(i)->Active(true);
			for (int j = 0; j < m_player1Hearts.at(i)->GetComponents()->size(); j++)
			{
				if (positionGot && spriteGot)
				{
					break;
				}
				else if (m_player1Hearts.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					if (i < 12 + armorHolder)
					{
						static_cast<SpriteComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->Direction(0);
					}
					else if ((float)i + 0.5 == 12 + (float)m_attributeComponents.at(0)->Armour() / 2)
					{
						static_cast<SpriteComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->Direction(1);
					}
					else
					{
						static_cast<SpriteComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->Direction(2);
					}
					spriteGot = true;
				}
				else if (m_player1Hearts.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					static_cast<PositionComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->setX(((i - 12) * 4) * 3);
					static_cast<PositionComponent*>(m_player1Hearts.at(i)->GetComponents()->at(j))->setY(8 * 3);
					positionGot = true;
				}
			}
		}
		else
		{
			m_player1Hearts.at(i)->Active(false);
		}
	}
}
void HealthSystem::PlayerTwoUpdate()
{
	int healthHolder = m_attributeComponents.at(1)->Health() / 2;
	int maxHealthHolder = m_attributeComponents.at(1)->MaxHealth() / 2;
	int armorHolder = m_attributeComponents.at(1)->Armour() / 2;
	int maxArmorHolder = m_attributeComponents.at(1)->MaxArmour() / 2;
	for (int i = 0; i < 12; i++)
	{
		bool spriteGot = false;
		bool positionGot = false;
		if (i < maxHealthHolder)
		{
			m_player2Hearts.at(i)->Active(true);
			for (int j = 0; j < m_player2Hearts.at(i)->GetComponents()->size(); j++)
			{
				if (positionGot && spriteGot)
				{
					break;
				}
				else if (m_player2Hearts.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					if (i < healthHolder)
					{
						static_cast<SpriteComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->Direction(0);
					}
					else if ((float)i + 0.5 == (float)m_attributeComponents.at(1)->Health() / 2)
					{
						static_cast<SpriteComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->Direction(1);
					}
					else
					{
						static_cast<SpriteComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->Direction(2);
					}
					spriteGot = true;
				}
				else if (m_player2Hearts.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					if (i < 6)
					{
						static_cast<PositionComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->setX(((i * 4) * 3) + ((24 * 3) * 2));
						static_cast<PositionComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->setY(0);
					}
					else
					{
						static_cast<PositionComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->setX((((i - 6) * 4) * 3) + ((24 * 3) * 2));
						static_cast<PositionComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->setY(4 * 3);
					}
					positionGot = true;
				}
			}
		}
		else
		{
			m_player2Hearts.at(i)->Active(false);
		}
	}
	for (int i = 12; i < 18; i++)
	{
		bool spriteGot = false;
		bool positionGot = false;
		if (i < 12 + maxArmorHolder)
		{
			m_player2Hearts.at(i)->Active(true);
			for (int j = 0; j < m_player2Hearts.at(i)->GetComponents()->size(); j++)
			{
				if (positionGot && spriteGot)
				{
					break;
				}
				else if (m_player2Hearts.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					if (i < 12 + armorHolder)
					{
						static_cast<SpriteComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->Direction(0);
					}
					else if ((float)i + 0.5 == 12 + (float)m_attributeComponents.at(1)->Armour() / 2)
					{
						static_cast<SpriteComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->Direction(1);
					}
					else
					{
						static_cast<SpriteComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->Direction(2);
					}
					spriteGot = true;
				}
				else if (m_player2Hearts.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					static_cast<PositionComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->setX((((i - 12) * 4) * 3) + ((24 * 3) * 2));
					static_cast<PositionComponent*>(m_player2Hearts.at(i)->GetComponents()->at(j))->setY(8 * 3);
					positionGot = true;
				}
			}
		}
		else
		{
			m_player2Hearts.at(i)->Active(false);
		}
	}
}

void HealthSystem::PlayerThreeUpdate()
{
	int healthHolder = m_attributeComponents.at(2)->Health() / 2;
	int maxHealthHolder = m_attributeComponents.at(2)->MaxHealth() / 2;
	int armorHolder = m_attributeComponents.at(2)->Armour() / 2;
	int maxArmorHolder = m_attributeComponents.at(2)->MaxArmour() / 2;
	for (int i = 0; i < 12; i++)
	{
		bool spriteGot = false;
		bool positionGot = false;
		if (i < maxHealthHolder)
		{
			m_player3Hearts.at(i)->Active(true);
			for (int j = 0; j < m_player3Hearts.at(i)->GetComponents()->size(); j++)
			{
				if (positionGot && spriteGot)
				{
					break;
				}
				else if (m_player3Hearts.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					if (i < healthHolder)
					{
						static_cast<SpriteComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->Direction(0);
					}
					else if ((float)i + 0.5 == (float)m_attributeComponents.at(2)->Health() / 2)
					{
						static_cast<SpriteComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->Direction(1);
					}
					else
					{
						static_cast<SpriteComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->Direction(2);
					}
					spriteGot = true;
				}
				else if (m_player3Hearts.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					if (i < 6)
					{
						static_cast<PositionComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->setX(((i * 4) * 3) + ((24 * 3) * 4));
						static_cast<PositionComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->setY(0);
					}
					else
					{
						static_cast<PositionComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->setX((((i - 6) * 4) * 3) + ((24 * 3) * 4));
						static_cast<PositionComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->setY(4 * 3);
					}
					positionGot = true;
				}
			}
		}
		else
		{
			m_player3Hearts.at(i)->Active(false);
		}
	}
	for (int i = 12; i < 18; i++)
	{
		bool spriteGot = false;
		bool positionGot = false;
		if (i < 12 + maxArmorHolder)
		{
			m_player3Hearts.at(i)->Active(true);
			for (int j = 0; j < m_player3Hearts.at(i)->GetComponents()->size(); j++)
			{
				if (positionGot && spriteGot)
				{
					break;
				}
				else if (m_player3Hearts.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					if (i < 12 + armorHolder)
					{
						static_cast<SpriteComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->Direction(0);
					}
					else if ((float)i + 0.5 == 12 + (float)m_attributeComponents.at(2)->Armour() / 2)
					{
						static_cast<SpriteComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->Direction(1);
					}
					else
					{
						static_cast<SpriteComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->Direction(2);
					}
					spriteGot = true;
				}
				else if (m_player3Hearts.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					static_cast<PositionComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->setX((((i - 12) * 4) * 3) + ((24 * 3) * 4));
					static_cast<PositionComponent*>(m_player3Hearts.at(i)->GetComponents()->at(j))->setY(8 * 3);
					positionGot = true;
				}
			}
		}
		else
		{
			m_player3Hearts.at(i)->Active(false);
		}
	}
}

void HealthSystem::PlayerFourUpdate()
{
	int healthHolder = m_attributeComponents.at(3)->Health() / 2;
	int maxHealthHolder = m_attributeComponents.at(3)->MaxHealth() / 2;
	int armorHolder = m_attributeComponents.at(3)->Armour() / 2;
	int maxArmorHolder = m_attributeComponents.at(3)->MaxArmour() / 2;
	for (int i = 0; i < 12; i++)
	{
		bool spriteGot = false;
		bool positionGot = false;
		if (i < maxHealthHolder)
		{
			m_player4Hearts.at(i)->Active(true);
			for (int j = 0; j < m_player4Hearts.at(i)->GetComponents()->size(); j++)
			{
				if (positionGot && spriteGot)
				{
					break;
				}
				else if (m_player4Hearts.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					if (i < healthHolder)
					{
						static_cast<SpriteComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->Direction(0);
					}
					else if ((float)i + 0.5 == (float)m_attributeComponents.at(3)->Health() / 2)
					{
						static_cast<SpriteComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->Direction(1);
					}
					else
					{
						static_cast<SpriteComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->Direction(2);
					}
					spriteGot = true;
				}
				else if (m_player4Hearts.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					if (i < 6)
					{
						static_cast<PositionComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->setX(((i * 4) * 3) + ((24 * 3) * 6));
						static_cast<PositionComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->setY(0);
					}
					else
					{
						static_cast<PositionComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->setX((((i - 6) * 4) * 3) + ((24 * 3) * 6));
						static_cast<PositionComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->setY(4 * 3);
					}
					positionGot = true;
				}
			}
		}
		else
		{
			m_player4Hearts.at(i)->Active(false);
		}
	}
	for (int i = 12; i < 18; i++)
	{
		bool spriteGot = false;
		bool positionGot = false;
		if (i < 12 + maxArmorHolder)
		{
			m_player4Hearts.at(i)->Active(true);
			for (int j = 0; j < m_player4Hearts.at(i)->GetComponents()->size(); j++)
			{
				if (positionGot && spriteGot)
				{
					break;
				}
				else if (m_player4Hearts.at(i)->GetComponents()->at(j)->Type() == "SC")
				{
					if (i < 12 + armorHolder)
					{
						static_cast<SpriteComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->Direction(0);
					}
					else if ((float)i + 0.5 == 12 + (float)m_attributeComponents.at(3)->Armour() / 2)
					{
						static_cast<SpriteComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->Direction(1);
					}
					else
					{
						static_cast<SpriteComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->Direction(2);
					}
					spriteGot = true;
				}
				else if (m_player4Hearts.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					static_cast<PositionComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->setX((((i - 12) * 4) * 3) + ((24 * 3) * 6));
					static_cast<PositionComponent*>(m_player4Hearts.at(i)->GetComponents()->at(j))->setY(8 * 3);
					positionGot = true;
				}
			}
		}
		else
		{
			m_player4Hearts.at(i)->Active(false);
		}
	}
}

void HealthSystem::CheckIfAllDead()
{
	bool allDead;
	if (m_entities.size() > 0)
	{
		allDead = true;
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (m_entities.at(i)->Active() == true)
			{
				allDead = false;
				break;
			}
		}
		if (allDead == true)
		{
			m_stateManager->GameOver = true;
			for (int i = 0; i < m_entities.size(); i++)
			{
				m_entities.at(i)->Active(true);
			}
		}
	}
	else
	{
		allDead = false;
	}

}
