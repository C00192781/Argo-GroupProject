#include "MenuSystem.h"

MenuSystem::MenuSystem()
{
	indexActiveMenu = -1;
}

MenuSystem::~MenuSystem()
{

}

void MenuSystem::Update()
{
	if (indexActiveMenu != -1)
	{
		int menuCKey = -1;
		for (int j = 0; j < m_entities.at(indexActiveMenu)->GetComponents()->size(); j++)
		{
			if (m_entities.at(indexActiveMenu)->GetComponents()->at(j)->Type() == "MenuC")
			{
				menuCKey = j;
			}
		}
		if (menuCKey >= 0)
		{
			MenuComponent* menu = static_cast<MenuComponent*>(m_entities.at(indexActiveMenu)->GetComponents()->at(menuCKey));
			for (int i = 0; i < menu->Buttons()->size(); i++)
			{
				int buttonCKey = -1;
				for (int j = 0; j < m_entities.at(indexActiveMenu)->GetComponents()->size(); j++)
				{
					if (m_entities.at(indexActiveMenu)->GetComponents()->at(j)->Type() == "ButtonC")
					{
						buttonCKey = j;
					}
				}
				if (buttonCKey == true)
				{
					if (static_cast<ButtonComponent*>(menu->Buttons()->at(i)->GetComponents()->at(buttonCKey))->Activated() == true)
					{
						if (menu->Buttons()->at(i)->ID() == "StartGame")
						{
							//startGame;
							std::cout << "Start The Game" << std::endl;
						}
						if (menu->Buttons()->at(i)->ID() == "ExitGame")
						{
							std::cout << "Close The Application" << std::endl;
							//exitGame;
						}
						if (menu->Buttons()->at(i)->ID() == "OptionsMenu")
						{
							std::cout << "Open Options Menu" << std::endl;
							//exitGame;
						}
					}
				}
			}
		}
	}

}

void MenuSystem::ChangeMenu(std::string ID)
{
	if (ID != activeMenuID)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (ID == "MainMenu")
			{
				indexActiveMenu = i;
				activeMenuID = "MainMenu";
				
			}
			else
			{
				std::cout << "Unknown ID" << std::endl;
			}
		}
	}
}

void MenuSystem::SetUpMainMenu()
{

}

void MenuSystem::RemoveMenu()
{

}
