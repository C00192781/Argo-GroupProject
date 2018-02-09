#include "MenuSystem.h"

MenuSystem::MenuSystem(EventListener * listener)
{
	m_eventListener = listener;
	indexActiveMenu = -1;
}

MenuSystem::~MenuSystem()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		RemoveMenu(m_entities.at(i)->ID());
	}
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
				for (int j = 0; j < menu->Buttons()->at(i)->GetComponents()->size(); j++)
				{
					if (menu->Buttons()->at(i)->GetComponents()->at(j)->Type() == "ButtonC")
					{
						buttonCKey = j;
					}
				}
				if (buttonCKey >= 0)
				{
					if (static_cast<ButtonComponent*>(menu->Buttons()->at(i)->GetComponents()->at(buttonCKey))->Activated() == true)
					{
						if (menu->Buttons()->at(i)->ID() == "StartGame")
						{
							std::cout << "Start The Game" << std::endl;
							m_eventListener->StartGame = true;
							//startGame;
						}
						if (menu->Buttons()->at(i)->ID() == "ExitGame")
						{
							std::cout << "Close The Application" << std::endl;
							m_eventListener->ExitGame = true;
							//exitGame;
						}
						if (menu->Buttons()->at(i)->ID() == "OpenOptions")
						{
							std::cout << "Open Options Menu" << std::endl;
							m_eventListener->GoToOptions = true;
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
	Entity * menu = new Entity("MainMenu");
	MenuComponent * menuC = new MenuComponent();

	Entity * buttonOne = new Entity("StartGame");
	buttonOne->AddComponent(new PositionComponent(SDL_Point{ 100, 100 }));
	buttonOne->AddComponent(new SpriteComponent("StartGameButton", 2, 2, 0, 0, 128, 32, 0));
	static_cast<SpriteComponent*>(buttonOne->GetComponents()->at(1))->IsAnimating(false);
	static_cast<SpriteComponent*>(buttonOne->GetComponents()->at(1))->Frame(1);
	buttonOne->AddComponent(new ButtonComponent(100, 100, 128, 32));


	Entity * buttonTwo = new Entity("OpenOptions");
	buttonTwo->AddComponent(new PositionComponent(SDL_Point{ 100, 300 }));
	buttonTwo->AddComponent(new SpriteComponent("OptionsButton", 2, 2, 0, 0, 128, 32, 0));
	static_cast<SpriteComponent*>(buttonTwo->GetComponents()->at(1))->IsAnimating(false);
	buttonTwo->AddComponent(new ButtonComponent(100, 300, 128, 32));

	Entity * buttonThree = new Entity("ExitGame");
	buttonThree->AddComponent(new PositionComponent(SDL_Point{ 100, 500 }));
	buttonThree->AddComponent(new SpriteComponent("ExitGameButton", 2, 2, 0, 0, 128, 32, 0));
	static_cast<SpriteComponent*>(buttonThree->GetComponents()->at(1))->IsAnimating(false);
	buttonThree->AddComponent(new ButtonComponent(100, 500, 128, 32));

	menuC->Buttons()->push_back(buttonOne);
	menuC->Buttons()->push_back(buttonTwo);
	menuC->Buttons()->push_back(buttonThree);

	menu->AddComponent(menuC);
	m_entities.push_back(menu);
}

Entity * MenuSystem::getMenu(std::string ID)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (ID == m_entities.at(i)->ID())
		{
			return m_entities.at(i);
		}
	}
	return nullptr;
}

void MenuSystem::RemoveMenu(std::string ID)
{
	for (int i = 0; i < GetMenuComponent(ID)->Buttons()->size(); i++)
	{
		delete GetMenuComponent(ID)->Buttons()->at(i);
	}
	GetMenuComponent(ID)->Buttons()->clear();
	GetMenuComponent(ID)->Buttons()->shrink_to_fit();
	for (std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end() ; ++it)
	{
		if ((*it)->ID() == ID)
		{
			m_entities.erase((it));
		}
	}


}

MenuComponent * MenuSystem::GetMenuComponent(std::string ID)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == ID)
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
				return static_cast<MenuComponent*>(m_entities.at(indexActiveMenu)->GetComponents()->at(menuCKey));
			}
			else
			{
				std::cout << "ERROR MENU COMPONENT NOT FOUND" << std::endl;
				return new MenuComponent();
			}
		}
	}
}