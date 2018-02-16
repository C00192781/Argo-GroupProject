#pragma once

#include "Instance.h"
#include "SystemManager.h"
#include "ValueComponent.h"

class ShopInstance : Instance
{
public:
	ShopInstance(SystemManager* s);
	~ShopInstance();

	void Generate(int luck);
	void Load();

	void Update() {};

private:

	SystemManager* m_systemManager;

	int m_itemOneGold;
	int m_itemTwoGold;
	int m_itemThreeGold;

};

