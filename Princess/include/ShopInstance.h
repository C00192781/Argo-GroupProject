#pragma once

#include "Instance.h"
#include "SystemManager.h"
#include "CurrencyComponent.h"
#include "WeaponComponent.h"

class ShopInstance : public Instance
{
public:
	ShopInstance(SystemManager* s, EventListener * e);
	~ShopInstance();

	void Generate(int luck);
	void Load();

	void Update() {};
	void Update(std::vector<Entity*> players);

private:

	int m_playerGold;
	TextComponent * m_playerGoldText;

	SystemManager* m_systemManager;

	int m_itemOneGold;
	int m_itemTwoGold;
	int m_itemThreeGold;

	ButtonComponent * m_buttonOne;
	ButtonComponent * m_buttonTwo;
	ButtonComponent * m_buttonThree;

	WeaponComponent * m_weaponOne;
	WeaponComponent * m_weaponTwo;
	WeaponComponent * m_weaponThree;

	int m_armorOne;
	int m_armorTwo;
	int m_armorThree;

	int m_healthOne;
	int m_healthTwo;
	int m_healthThree;

	std::string m_itemNameOne;
	std::string m_itemNameTwo;
	std::string m_itemNameThree;

	bool m_weaponOneSwitch;
	bool m_weaponTwoSwitch;
	bool m_weaponThreeSwitch;

	int m_timer = 0;

	EventListener * m_listener;

};

