#include "ShopInstance.h"



ShopInstance::ShopInstance(SystemManager* s, EventListener * e)
{
	m_systemManager = s;
	m_listener = e;
}

ShopInstance::~ShopInstance()
{
}

void ShopInstance::Generate(int luck)
{

	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities.at(i);
	}
	m_entities.clear();

	int randHolder = rand() % 2;
	if (randHolder >= 1)
	{
		randHolder = rand() % 3;
		if (randHolder >= 2)
		{
			m_itemNameOne = "Staff of";
			m_weaponOne = new WeaponComponent(WeaponType(2));
			m_entities.push_back(new Entity("Item1"));
			SpriteComponent * sprite = new SpriteComponent("Wand", 4, 0, 0, 0, 64, 32, 0);
			sprite->Relative(true);
			m_entities.back()->AddComponent(sprite);
			m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 100 }));
		}
		else if (randHolder >= 1)
		{
			m_itemNameOne = "Bow of";
			m_weaponOne = new WeaponComponent(WeaponType(1));
			m_entities.push_back(new Entity("Item1"));
			SpriteComponent * sprite = new SpriteComponent("Bow", 4, 0, 0, 0, 64, 32, 0);
			sprite->Relative(true);
			m_entities.back()->AddComponent(sprite);
			m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 100 }));
		}
		else
		{
			m_itemNameOne = "Sword of";
			m_weaponOne = new WeaponComponent(WeaponType(0));
			m_entities.push_back(new Entity("Item1"));
			SpriteComponent * sprite = new SpriteComponent("Sword", 4, 0, 0, 0, 64, 32, 0);
			sprite->Relative(true);
			m_entities.back()->AddComponent(sprite);
			m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 100 }));
		}
		m_weaponOneSwitch = true;
		randHolder = rand() % 20;
		if (randHolder >= 19)m_itemNameOne += " Magic";
		else if (randHolder >= 18)m_itemNameOne += " Stuff";
		else if (randHolder >= 17)m_itemNameOne += " Demons";
		else if (randHolder >= 16)m_itemNameOne += " Hair";
		else if (randHolder >= 15)m_itemNameOne += " Eyeballs";
		else if (randHolder >= 14)m_itemNameOne += " Other Hair";
		else if (randHolder >= 13)m_itemNameOne += " Other Stuff";
		else if (randHolder >= 12)m_itemNameOne += " Picheal Phelps";
		else if (randHolder >= 11)m_itemNameOne += " Gluglax";
		else if (randHolder >= 10)m_itemNameOne += " Manly Tears";
		else if (randHolder >= 9)m_itemNameOne += " Womanly Tears";
		else if (randHolder >= 8)m_itemNameOne += " Endless Tears";
		else if (randHolder >= 7)m_itemNameOne += " Salty Tears";
		else if (randHolder >= 6)m_itemNameOne += " Bloody Tears";
		else if (randHolder >= 5)m_itemNameOne += " Normalness";
		else if (randHolder >= 4)m_itemNameOne += " Elemental Magic";
		else if (randHolder >= 3)m_itemNameOne += " Fire";
		else if (randHolder >= 2)m_itemNameOne += " Water";
		else if (randHolder >= 1)m_itemNameOne += " Air";
		else m_itemNameOne += " Earth";
	}
	else
	{
		m_itemNameOne = "Armour of";
		m_entities.push_back(new Entity("Item1"));
		SpriteComponent * sprite = new SpriteComponent("Armor", 4, 0, 0, 0, 64, 32, 0);
		sprite->Relative(true);
		m_entities.back()->AddComponent(sprite);
		m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 100 }));
		m_weaponOneSwitch = false;
		randHolder = rand() % 20;
		if (randHolder >= 19)m_itemNameOne += " Magic";
		else if (randHolder >= 18)m_itemNameOne += " Stuff";
		else if (randHolder >= 17)m_itemNameOne += " Demons";
		else if (randHolder >= 16)m_itemNameOne += " Hair";
		else if (randHolder >= 15)m_itemNameOne += " Eyeballs";
		else if (randHolder >= 14)m_itemNameOne += " Other Hair";
		else if (randHolder >= 13)m_itemNameOne += " Other Stuff";
		else if (randHolder >= 12)m_itemNameOne += " Picheal Phelps";
		else if (randHolder >= 11)m_itemNameOne += " Gluglax";
		else if (randHolder >= 10)m_itemNameOne += " Manly Tears";
		else if (randHolder >= 9)m_itemNameOne += " Womanly Tears";
		else if (randHolder >= 8)m_itemNameOne += " Endless Tears";
		else if (randHolder >= 7)m_itemNameOne += " Salty Tears";
		else if (randHolder >= 6)m_itemNameOne += " Bloody Tears";
		else if (randHolder >= 5)m_itemNameOne += " Normalness";
		else if (randHolder >= 4)m_itemNameOne += " Elemental Magic";
		else if (randHolder >= 3)m_itemNameOne += " Fire";
		else if (randHolder >= 2)m_itemNameOne += " Water";
		else if (randHolder >= 1)m_itemNameOne += " Air";
		else m_itemNameOne += " Earth";
	}
	m_itemOneGold = rand() % 1000 + 50;
	m_entities.push_back(new Entity("ItemCost1"));
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 492, 100 }));
	m_entities.back()->AddComponent(new TextComponent("munro", std::to_string(m_itemOneGold) + " Gold", SDL_Color{ 255,255,255,255 }, 32 * 6, 16 * 3));

	randHolder = rand() % 2;
	if (randHolder >= 1)
	{
		randHolder = rand() % 3;
		if (randHolder >= 2)
		{
			m_itemNameTwo = "Staff of";
			m_weaponTwo = new WeaponComponent(WeaponType(2));
			m_entities.push_back(new Entity("Item2"));
			SpriteComponent * sprite = new SpriteComponent("Wand", 4, 0, 0, 0, 64, 32, 0);
			sprite->Relative(true);
			m_entities.back()->AddComponent(sprite);
			m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 250 }));
		}
		else if (randHolder >= 1)
		{
			m_itemNameTwo = "Bow of";
			m_weaponTwo = new WeaponComponent(WeaponType(1));
			m_entities.push_back(new Entity("Item2"));
			SpriteComponent * sprite = new SpriteComponent("Bow", 4, 0, 0, 0, 64, 32, 0);
			sprite->Relative(true);
			m_entities.back()->AddComponent(sprite);
			m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 250 }));
		}
		else
		{
			m_itemNameTwo = "Sword of";
			m_weaponTwo = new WeaponComponent(WeaponType(0));
			m_entities.push_back(new Entity("Item2"));
			SpriteComponent * sprite = new SpriteComponent("Sword", 4, 0, 0, 0, 64, 32, 0);
			sprite->Relative(true);
			m_entities.back()->AddComponent(sprite);
			m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 250 }));
		}
		m_weaponOneSwitch = true;
		randHolder = rand() % 20;
		if (randHolder >= 19)m_itemNameTwo += " Magic";
		else if (randHolder >= 18)m_itemNameTwo += " Stuff";
		else if (randHolder >= 17)m_itemNameTwo += " Demons";
		else if (randHolder >= 16)m_itemNameTwo += " Hair";
		else if (randHolder >= 15)m_itemNameTwo += " Eyeballs";
		else if (randHolder >= 14)m_itemNameTwo += " Other Hair";
		else if (randHolder >= 13)m_itemNameTwo += " Other Stuff";
		else if (randHolder >= 12)m_itemNameTwo += " Picheal Phelps";
		else if (randHolder >= 11)m_itemNameTwo += " Gluglax";
		else if (randHolder >= 10)m_itemNameTwo += " Manly Tears";
		else if (randHolder >= 9)m_itemNameTwo += " Womanly Tears";
		else if (randHolder >= 8)m_itemNameTwo += " Endless Tears";
		else if (randHolder >= 7)m_itemNameTwo += " Salty Tears";
		else if (randHolder >= 6)m_itemNameTwo += " Bloody Tears";
		else if (randHolder >= 5)m_itemNameTwo += " Normalness";
		else if (randHolder >= 4)m_itemNameTwo += " Elemental Magic";
		else if (randHolder >= 3)m_itemNameTwo += " Fire";
		else if (randHolder >= 2)m_itemNameTwo += " Water";
		else if (randHolder >= 1)m_itemNameTwo += " Air";
		else m_itemNameTwo += " Earth";
	}
	else
	{
		m_itemNameTwo = "Armour of";
		m_entities.push_back(new Entity("Item2"));
		SpriteComponent * sprite = new SpriteComponent("Armor", 4, 0, 0, 0, 64, 32, 0);
		sprite->Relative(true);
		m_entities.back()->AddComponent(sprite);
		m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 250 }));
		m_weaponOneSwitch = false;
		randHolder = rand() % 20;
		if (randHolder >= 19)m_itemNameTwo += " Magic";
		else if (randHolder >= 18)m_itemNameTwo += " Stuff";
		else if (randHolder >= 17)m_itemNameTwo += " Demons";
		else if (randHolder >= 16)m_itemNameTwo += " Hair";
		else if (randHolder >= 15)m_itemNameTwo += " Eyeballs";
		else if (randHolder >= 14)m_itemNameTwo += " Other Hair";
		else if (randHolder >= 13)m_itemNameTwo += " Other Stuff";
		else if (randHolder >= 12)m_itemNameTwo += " Picheal Phelps";
		else if (randHolder >= 11)m_itemNameTwo += " Gluglax";
		else if (randHolder >= 10)m_itemNameTwo += " Manly Tears";
		else if (randHolder >= 9)m_itemNameTwo += " Womanly Tears";
		else if (randHolder >= 8)m_itemNameTwo += " Endless Tears";
		else if (randHolder >= 7)m_itemNameTwo += " Salty Tears";
		else if (randHolder >= 6)m_itemNameTwo += " Bloody Tears";
		else if (randHolder >= 5)m_itemNameTwo += " Normalness";
		else if (randHolder >= 4)m_itemNameTwo += " Elemental Magic";
		else if (randHolder >= 3)m_itemNameTwo += " Fire";
		else if (randHolder >= 2)m_itemNameTwo += " Water";
		else if (randHolder >= 1)m_itemNameTwo += " Air";
		else m_itemNameTwo += " Earth";
	}
	m_itemTwoGold = rand() % 1000 + 50;
	m_entities.push_back(new Entity("ItemCost2"));
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 492, 250 }));
	m_entities.back()->AddComponent(new TextComponent("munro", std::to_string(m_itemTwoGold) + " Gold", SDL_Color{ 255,255,255,255 }, 32 * 6, 16 * 3));

	randHolder = rand() % 2;
	if (randHolder >= 1)
	{
		randHolder = rand() % 3;
		if (randHolder >= 2)
		{
			m_itemNameThree = "Staff of";
			m_weaponThree = new WeaponComponent(WeaponType(2));
			m_entities.push_back(new Entity("Item2"));
			SpriteComponent * sprite = new SpriteComponent("Wand", 4, 0, 0, 0, 64, 32, 0);
			sprite->Relative(true);
			m_entities.back()->AddComponent(sprite);
			m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 400 }));
		}
		else if (randHolder >= 1)
		{
			m_itemNameThree = "Bow of";
			m_weaponThree = new WeaponComponent(WeaponType(1));
			m_entities.push_back(new Entity("Item2"));
			SpriteComponent * sprite = new SpriteComponent("Bow", 4, 0, 0, 0, 64, 32, 0);
			sprite->Relative(true);
			m_entities.back()->AddComponent(sprite);
			m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 400 }));
		}
		else
		{
			m_itemNameThree = "Sword of";
			m_weaponThree = new WeaponComponent(WeaponType(0));
 			m_entities.push_back(new Entity("Item2"));
			SpriteComponent * sprite = new SpriteComponent("Sword", 4, 0, 0, 0, 64, 32, 0);
			sprite->Relative(true);
			m_entities.back()->AddComponent(sprite);
			m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 400 }));
		}
		m_weaponOneSwitch = true;
		randHolder = rand() % 20;
		if (randHolder >= 19)m_itemNameThree += " Magic";
		else if (randHolder >= 18)m_itemNameThree += " Stuff";
		else if (randHolder >= 17)m_itemNameThree += " Demons";
		else if (randHolder >= 16)m_itemNameThree += " Hair";
		else if (randHolder >= 15)m_itemNameThree += " Eyeballs";
		else if (randHolder >= 14)m_itemNameThree += " Other Hair";
		else if (randHolder >= 13)m_itemNameThree += " Other Stuff";
		else if (randHolder >= 12)m_itemNameThree += " Picheal Phelps";
		else if (randHolder >= 11)m_itemNameThree += " Gluglax";
		else if (randHolder >= 10)m_itemNameThree += " Manly Tears";
		else if (randHolder >= 9)m_itemNameThree += " Womanly Tears";
		else if (randHolder >= 8)m_itemNameThree += " Endless Tears";
		else if (randHolder >= 7)m_itemNameThree += " Salty Tears";
		else if (randHolder >= 6)m_itemNameThree += " Bloody Tears";
		else if (randHolder >= 5)m_itemNameThree += " Normalness";
		else if (randHolder >= 4)m_itemNameThree += " Elemental Magic";
		else if (randHolder >= 3)m_itemNameThree += " Fire";
		else if (randHolder >= 2)m_itemNameThree += " Water";
		else if (randHolder >= 1)m_itemNameThree += " Air";
		else m_itemNameThree += " Earth";
	}
	else
	{
		m_itemNameThree = "Armour of";
		m_entities.push_back(new Entity("Item2"));
		SpriteComponent * sprite = new SpriteComponent("Armor", 4, 0, 0, 0, 64, 32, 0);
		sprite->Relative(true);
		m_entities.back()->AddComponent(sprite);
		m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 400 }));
		m_weaponOneSwitch = false;
		randHolder = rand() % 20;
		if (randHolder >= 19)m_itemNameThree += " Magic";
		else if (randHolder >= 18)m_itemNameThree += " Stuff";
		else if (randHolder >= 17)m_itemNameThree += " Demons";
		else if (randHolder >= 16)m_itemNameThree += " Hair";
		else if (randHolder >= 15)m_itemNameThree += " Eyeballs";
		else if (randHolder >= 14)m_itemNameThree += " Other Hair";
		else if (randHolder >= 13)m_itemNameThree += " Other Stuff";
		else if (randHolder >= 12)m_itemNameThree += " Picheal Phelps";
		else if (randHolder >= 11)m_itemNameThree += " Gluglax";
		else if (randHolder >= 10)m_itemNameThree += " Manly Tears";
		else if (randHolder >= 9)m_itemNameThree += " Womanly Tears";
		else if (randHolder >= 8)m_itemNameThree += " Endless Tears";
		else if (randHolder >= 7)m_itemNameThree += " Salty Tears";
		else if (randHolder >= 6)m_itemNameThree += " Bloody Tears";
		else if (randHolder >= 5)m_itemNameThree += " Normalness";
		else if (randHolder >= 4)m_itemNameThree += " Elemental Magic";
		else if (randHolder >= 3)m_itemNameThree += " Fire";
		else if (randHolder >= 2)m_itemNameThree += " Water";
		else if (randHolder >= 1)m_itemNameThree += " Air";
		else m_itemNameThree += " Earth";
	}
	m_itemThreeGold = rand() % 1000 + 50;
	m_entities.push_back(new Entity("ItemCost2"));
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 492, 400 }));
	m_entities.back()->AddComponent(new TextComponent("munro", std::to_string(m_itemThreeGold) + " Gold", SDL_Color{ 255,255,255,255 }, 32 * 6, 16 * 3));

	m_entities.push_back(new Entity("Item1Button"));
	SpriteComponent * sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 50 + 74 }));
	m_buttonOne = new ButtonComponent(0, 0, 32 * 3, 16 * 3);
	m_entities.back()->AddComponent(m_buttonOne);
	m_entities.back()->AddComponent(new TextComponent("munro", "Buy", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("Item1"));
	sprite = new SpriteComponent("Plate", 3, 0, 0, 0, 64, 32, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 100 }));
	m_entities.back()->AddComponent(new TextComponent("munro", m_itemNameOne, SDL_Color{ 255,255,255,255 }, 32 * 6, 16 * 3));

	m_entities.push_back(new Entity("Item2Button"));
	sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 274 }));
	m_buttonTwo = new ButtonComponent(0, 0, 32 * 3, 16 * 3);
	m_entities.back()->AddComponent(m_buttonTwo);
	m_entities.back()->AddComponent(new TextComponent("munro", "Buy", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("Item2"));
	sprite = new SpriteComponent("Plate", 3, 0, 0, 0, 64, 32, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 250 }));
	m_entities.back()->AddComponent(new TextComponent("munro", m_itemNameTwo, SDL_Color{ 255,255,255,255 }, 32 * 6, 16 * 3));

	m_entities.push_back(new Entity("Item3Button"));
	sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 424 }));
	m_buttonThree = new ButtonComponent(0, 0, 32 * 3, 16 * 3);
	m_entities.back()->AddComponent(m_buttonThree);
	m_entities.back()->AddComponent(new TextComponent("munro", "Buy", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("LeaveButton"));
	sprite = new SpriteComponent("Button", 3, 0, 0, 0, 32, 16, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 100, 524 }));
	m_entities.back()->AddComponent(new ButtonComponent(0, 0, 32 * 3, 16 * 3));
	m_entities.back()->AddComponent(new TextComponent("munro", "Leave", SDL_Color{ 255,255,255,255 }, 32 * 3, 16 * 3));

	m_entities.push_back(new Entity("Item3"));
	sprite = new SpriteComponent("Plate", 3, 0, 0, 0, 64, 32, 0);
	sprite->Relative(true);
	m_entities.back()->AddComponent(sprite);
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 300, 400 }));
	m_entities.back()->AddComponent(new TextComponent("munro", m_itemNameThree, SDL_Color{ 255,255,255,255 }, 32 * 6, 16 * 3));

	m_entities.push_back(new Entity("Item3"));
	m_entities.back()->AddComponent(new PositionComponent(SDL_Point{ 0, 0 }));
	m_playerGoldText = new TextComponent("munro", "Gold: " + std::to_string(m_playerGold), SDL_Color{ 255,255,255,255 }, 32 * 6, 16 * 3);
	m_entities.back()->AddComponent(m_playerGoldText);

	Load();
}
void ShopInstance::Load()
{
	m_systemManager->renderSystem->SelectiveClear();
	m_systemManager->buttonSystem->SelectiveClear();
	m_systemManager->textRenderSystem->SelectiveClear();

	for (int i = 0; i < m_entities.size(); i++)
	{
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			if (m_entities.at(i)->GetComponents()->at(j)->Type() == "SC")
			{
				m_systemManager->renderSystem->AddEntity(m_entities.at(i));
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "ButtonC")
			{
				m_systemManager->buttonSystem->AddEntity(m_entities.at(i));
			}
			else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "TextComponent")
			{
				m_systemManager->textRenderSystem->AddEntity(m_entities.at(i));
			}
		}
	}
}

void ShopInstance::Update(std::vector<Entity*> players)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players.at(i)->Control())
		{
			for (int j = 0; j < players.at(i)->GetComponents()->size(); j++)
			{
				if (players.at(i)->GetComponents()->at(j)->Type() == "currency")
				{
					m_playerGold = static_cast<CurrencyComponent*>(players.at(i)->GetComponents()->at(j))->value();
					m_playerGoldText->Text("Gold: " + std::to_string(m_playerGold));
					break;
				}
			}
			break;
		}
	}



	for(int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == "LeaveButton" && static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated())
		{
			m_listener->ShopToTown = true;
			static_cast<ButtonComponent*>(m_entities.at(i)->FindComponent("ButtonC"))->Activated(false);
		}
	}
	if(m_timer <= 0)
	{
		if (m_buttonOne->Activated())
		{
			for (int i = 0; i < players.size(); i++)
			{
				if (players.at(i)->Control())
				{
					bool proceed = false;
					for (int j = 0; j < players.at(i)->GetComponents()->size(); j++)
					{
						if (players.at(i)->GetComponents()->at(j)->Type() == "currency")
						{
							if (static_cast<CurrencyComponent*>(players.at(i)->GetComponents()->at(j))->value() >= m_itemOneGold)
							{
								static_cast<CurrencyComponent*>(players.at(i)->GetComponents()->at(j))->value(static_cast<CurrencyComponent*>(players.at(i)->GetComponents()->at(j))->value() - m_itemOneGold);
								proceed = true;
							}
						}
					}
					if (proceed)
					{
						if (m_weaponOneSwitch)
						{
							for (int j = 0; j < players.at(i)->GetComponents()->size(); j++)
							{
								if (players.at(i)->GetComponents()->at(j)->Type() == "weapon")
								{
									//delete players.at(i)->GetComponents()->at(j);
									players.at(i)->GetComponents()->at(j) = m_weaponOne;
									m_listener->ChangedWeapon = true;
									break;
								}
							}
						}
						else
						{
							for (int j = 0; j < players.at(i)->GetComponents()->size(); j++)
							{
								if (players.at(i)->GetComponents()->at(j)->Type() == "attribute")
								{
									static_cast<AttributesComponent*>(players.at(i)->GetComponents()->at(j))->AdditiveArmour(m_armorOne);
									static_cast<AttributesComponent*>(players.at(i)->GetComponents()->at(j))->AdditiveHealth(m_healthOne);
									m_listener->ChangedArmor = true;
									break;
								}
							}
						}
					}
				}
			}
			m_timer = 100;
		}
		else if (m_buttonTwo->Activated())
		{
			for (int i = 0; i < players.size(); i++)
			{
				if (players.at(i)->Control())
				{
					bool proceed = false;
					for (int j = 0; j < players.at(i)->GetComponents()->size(); j++)
					{
						if (players.at(i)->GetComponents()->at(j)->Type() == "currency")
						{
							if (static_cast<CurrencyComponent*>(players.at(i)->GetComponents()->at(j))->value() >= m_itemTwoGold)
							{
								static_cast<CurrencyComponent*>(players.at(i)->GetComponents()->at(j))->value(static_cast<CurrencyComponent*>(players.at(i)->GetComponents()->at(j))->value() - m_itemTwoGold);
								proceed = true;
							}
						}
					}
					if (proceed)
					{
						if (m_weaponTwoSwitch)
						{
							for (int j = 0; j < players.at(i)->GetComponents()->size(); j++)
							{
								if (players.at(i)->GetComponents()->at(j)->Type() == "weapon")
								{
									//delete players.at(i)->GetComponents()->at(j);
									players.at(i)->GetComponents()->at(j) = m_weaponTwo;
									m_listener->ChangedWeapon = true;
									break;
								}
							}
						}
						else
						{
							for (int j = 0; j < players.at(i)->GetComponents()->size(); j++)
							{
								if (players.at(i)->GetComponents()->at(j)->Type() == "attribute")
								{
									static_cast<AttributesComponent*>(players.at(i)->GetComponents()->at(j))->AdditiveArmour(m_armorTwo);
									static_cast<AttributesComponent*>(players.at(i)->GetComponents()->at(j))->AdditiveHealth(m_healthTwo);
									m_listener->ChangedArmor = true;
									break;
								}
							}
						}
					}
				}
			}
			m_timer = 100;
		}
		else if (m_buttonThree->Activated())
		{
			for (int i = 0; i < players.size(); i++)
			{
				if (players.at(i)->Control())
				{
					bool proceed = false;
					for (int j = 0; j < players.at(i)->GetComponents()->size(); j++)
					{
						if (players.at(i)->GetComponents()->at(j)->Type() == "currency")
						{
							if (static_cast<CurrencyComponent*>(players.at(i)->GetComponents()->at(j))->value() >= m_itemThreeGold)
							{
								static_cast<CurrencyComponent*>(players.at(i)->GetComponents()->at(j))->value(static_cast<CurrencyComponent*>(players.at(i)->GetComponents()->at(j))->value() - m_itemThreeGold);
								proceed = true;
							}
						}
					}
					if (proceed)
					{
						if (m_weaponThreeSwitch)
						{
							for (int j = 0; j < players.at(i)->GetComponents()->size(); j++)
							{
								if (players.at(i)->GetComponents()->at(j)->Type() == "weapon")
								{
									//delete players.at(i)->GetComponents()->at(j);
									players.at(i)->GetComponents()->at(j) = m_weaponThree;
									m_listener->ChangedWeapon = true;
									break;
								}
							}
						}
						else
						{
							for (int j = 0; j < players.at(i)->GetComponents()->size(); j++)
							{
								if (players.at(i)->GetComponents()->at(j)->Type() == "attribute")
								{
									static_cast<AttributesComponent*>(players.at(i)->GetComponents()->at(j))->AdditiveArmour(m_armorThree);
									static_cast<AttributesComponent*>(players.at(i)->GetComponents()->at(j))->AdditiveHealth(m_healthThree);
									m_listener->ChangedArmor = true;
									break;
								}
							}
						}
					}
				}
			}
			m_timer = 100;
		}
	}
	else
	{
		m_timer--;
	}
}