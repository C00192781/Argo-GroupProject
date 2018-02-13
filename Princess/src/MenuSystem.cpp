#include "MenuSystem.h"

MenuSystem::MenuSystem(EventListener * listener)
{
	m_eventListener = listener;
	indexActiveMenu = -1;
	menuTimer = 0;
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
	for (int i = 0; i < m_entities.size(); i++)
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
				MenuComponent* menu = static_cast<MenuComponent*>(m_entities.at(i)->GetComponents()->at(menuCKey));
				for (int j = 0; j < menu->Buttons()->size(); j++)
				{
					int scKey = -1;
					int buttonCKey = -1;
					int pcKey = -1;
					for (int k = 0; k < menu->Buttons()->at(j)->GetComponents()->size(); k++)
					{
						if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "SC")
						{
							scKey = k;
						}
						if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "PC")
						{
							pcKey = k;
						}
						if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "ButtonC")
						{
							buttonCKey = k;
						}
					}
					if (scKey >= 0 && buttonCKey >= 0 && pcKey >= 0)
					{
						SDL_Point p = SDL_Point{ -1, -1 };
						SDL_GetMouseState(&p.x, &p.y);
						SDL_Rect *r = &static_cast<SpriteComponent*>(menu->Buttons()->at(j)->GetComponents()->at(scKey))->GetRect();
						SDL_Point *buttonPos = &static_cast<PositionComponent*>(menu->Buttons()->at(j)->GetComponents()->at(pcKey))->getPosition();
						SDL_Rect rect = SDL_Rect();
						rect.x = r->x + buttonPos->x;
						rect.y = r->y + buttonPos->y;
						rect.w = r->w*GAME_SCALE;
						rect.h = r->h*GAME_SCALE;
						if (SDL_PointInRect(&p, &rect) == true)
						{
							if (m_eventListener->LeftClick)
							{
								static_cast<ButtonComponent*>(menu->Buttons()->at(j)->GetComponents()->at(buttonCKey))->Activated(true);
							}
							else
							{
								int scTwoKey = -1;
								int buttonCTwoKey = -1;
								for (int k = 0; k < menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->size(); k++)
								{
									if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "SC")
									{
										scTwoKey = k;
									}
									if (menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->at(k)->Type() == "ButtonC")
									{
										buttonCTwoKey = k;
									}
								}
								if (scKey >= 0 && buttonCKey >= 0)
								{
									static_cast<ButtonComponent*>(menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->at(buttonCTwoKey))->Selected(false);
									static_cast<SpriteComponent*>(menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->at(scTwoKey))->Frame(0);

									menu->SelectedButtonIndex(j);
									std::cout << menu->SelectedButtonIndex() << std::endl;

									static_cast<ButtonComponent*>(menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->at(buttonCKey))->Selected(true);
									static_cast<SpriteComponent*>(menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->at(scKey))->Frame(1);
								}
							}
						}
					}
				}
				if (menuTimer > 2)
				{
					for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
					{
						if (m_eventListener->W)
						{
							MenuComponent* menu = static_cast<MenuComponent*>(m_entities.at(i)->GetComponents()->at(menuCKey));
							if (menu->SelectedButtonIndex() == 0)
							{
								int buttonCOneKey = -1;
								int scOneKey = -1;
								for (int k = 0; k < menu->Buttons()->at(0)->GetComponents()->size(); k++)
								{
									if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "ButtonC")
									{
										buttonCOneKey = k;
									}
									if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "SC")
									{
										scOneKey = k;
									}
								}

								int buttonCTwoKey = -1;
								int scTwoKey = -1;
								for (int k = 0; k < menu->Buttons()->at(menu->Buttons()->size() - 1)->GetComponents()->size(); k++)
								{
									if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "ButtonC")
									{
										buttonCTwoKey = k;
									}
									if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "SC")
									{
										scTwoKey = k;
									}
								}
								if (scOneKey >= 0 && scTwoKey >= 0 && buttonCOneKey >= 0 && buttonCTwoKey >= 0)
								{
									static_cast<ButtonComponent*>(menu->Buttons()->at(0)->GetComponents()->at(buttonCOneKey))->Selected(false);
									static_cast<SpriteComponent*>(menu->Buttons()->at(0)->GetComponents()->at(scOneKey))->Frame(0);

									static_cast<ButtonComponent*>(menu->Buttons()->at(menu->Buttons()->size() - 1)->GetComponents()->at(buttonCTwoKey))->Selected(true);
									static_cast<SpriteComponent*>(menu->Buttons()->at(menu->Buttons()->size() - 1)->GetComponents()->at(scTwoKey))->Frame(1);

									menu->SelectedButtonIndex(menu->Buttons()->size() - 1);
									std::cout << menu->SelectedButtonIndex() << std::endl;
								}

							}
							else
							{
								for (int j = 0; j < menu->Buttons()->size(); j++)
								{
									if (j == menu->SelectedButtonIndex())
									{
										int buttonOneCKey = -1;
										int scOneKey = -1;
										for (int k = 0; k < menu->Buttons()->at(j)->GetComponents()->size(); k++)
										{
											if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "ButtonC")
											{
												buttonOneCKey = k;
											}
											if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "SC")
											{
												scOneKey = k;
											}
										}
										int buttonTwoCKey = -1;
										int scTwoKey = -1;
										for (int k = 0; k < menu->Buttons()->at(j - 1)->GetComponents()->size(); k++)
										{
											if (menu->Buttons()->at(j - 1)->GetComponents()->at(k)->Type() == "ButtonC")
											{
												buttonTwoCKey = k;
											}
											if (menu->Buttons()->at(j - 1)->GetComponents()->at(k)->Type() == "SC")
											{
												scTwoKey = k;
											}
										}
										if (scOneKey >= 0 && scTwoKey >= 0 && buttonOneCKey >= 0 && buttonTwoCKey >= 0)
										{
											static_cast<ButtonComponent*>(menu->Buttons()->at(j)->GetComponents()->at(buttonOneCKey))->Selected(false);
											static_cast<SpriteComponent*>(menu->Buttons()->at(j)->GetComponents()->at(scOneKey))->Frame(0);

											static_cast<ButtonComponent*>(menu->Buttons()->at((j - 1))->GetComponents()->at(buttonTwoCKey))->Selected(true);
											static_cast<SpriteComponent*>(menu->Buttons()->at((j - 1))->GetComponents()->at(scTwoKey))->Frame(1);

											menu->SelectedButtonIndex((j - 1));
											std::cout << menu->SelectedButtonIndex() << std::endl;
											break;
										}
									}
								}
							}
							menuTimer = 0;
						}
						else if (m_eventListener->S)
						{
							MenuComponent* menu = static_cast<MenuComponent*>(m_entities.at(i)->GetComponents()->at(menuCKey));
							if (menu->SelectedButtonIndex() == (menu->Buttons()->size() - 1))
							{
								int buttonCOneKey = -1;
								int scOneKey = -1;
								for (int k = 0; k < menu->Buttons()->at(0)->GetComponents()->size(); k++)
								{
									if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "ButtonC")
									{
										buttonCOneKey = k;
									}
									if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "SC")
									{
										scOneKey = k;
									}
								}

								int buttonCTwoKey = -1;
								int scTwoKey = -1;
								for (int k = 0; k < menu->Buttons()->at(menu->Buttons()->size() - 1)->GetComponents()->size(); k++)
								{
									if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "ButtonC")
									{
										buttonCTwoKey = k;
									}
									if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "SC")
									{
										scTwoKey = k;
									}
								}
								if (buttonCOneKey >= 0 && buttonCTwoKey)
								{
									static_cast<ButtonComponent*>(menu->Buttons()->at(menu->Buttons()->size() - 1)->GetComponents()->at(buttonCOneKey))->Selected(false);
									static_cast<SpriteComponent*>(menu->Buttons()->at(menu->Buttons()->size() - 1)->GetComponents()->at(scTwoKey))->Frame(0);

									static_cast<ButtonComponent*>(menu->Buttons()->at(0)->GetComponents()->at(buttonCTwoKey))->Selected(true);
									static_cast<SpriteComponent*>(menu->Buttons()->at(0)->GetComponents()->at(scOneKey))->Frame(1);
									menu->SelectedButtonIndex(0);
									std::cout << menu->SelectedButtonIndex() << std::endl;
								}

							}
							else
							{
								for (int j = 0; j < menu->Buttons()->size(); j++)
								{
									if (j == menu->SelectedButtonIndex())
									{
										int buttonOneCKey = -1;
										int scOneKey = -1;
										for (int k = 0; k < menu->Buttons()->at(j)->GetComponents()->size(); k++)
										{
											if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "ButtonC")
											{
												buttonOneCKey = k;
											}
											if (menu->Buttons()->at(j)->GetComponents()->at(k)->Type() == "SC")
											{
												scOneKey = k;
											}
										}

										int buttonTwoCKey = -1;
										int scTwoKey = -1;
										for (int k = 0; k < menu->Buttons()->at(j + 1)->GetComponents()->size(); k++)
										{
											if (menu->Buttons()->at(j + 1)->GetComponents()->at(k)->Type() == "ButtonC")
											{
												buttonTwoCKey = k;
											}
											if (menu->Buttons()->at(j + 1)->GetComponents()->at(k)->Type() == "SC")
											{
												scTwoKey = k;
											}
										}

										if (buttonOneCKey >= 0 && buttonTwoCKey >= 0)
										{
											static_cast<ButtonComponent*>(menu->Buttons()->at(j)->GetComponents()->at(buttonOneCKey))->Selected(false);
											static_cast<SpriteComponent*>(menu->Buttons()->at(j)->GetComponents()->at(scOneKey))->Frame(0);

											static_cast<ButtonComponent*>(menu->Buttons()->at((j + 1))->GetComponents()->at(buttonTwoCKey))->Selected(true);
											static_cast<SpriteComponent*>(menu->Buttons()->at((j + 1))->GetComponents()->at(scTwoKey))->Frame(1);

											menu->SelectedButtonIndex((j + 1));
											std::cout << menu->SelectedButtonIndex() << std::endl;
											break;
										}
									}
								}
							}
							menuTimer = 0;
						}
						else if (m_eventListener->Space)
						{
							MenuComponent* menu = static_cast<MenuComponent*>(m_entities.at(i)->GetComponents()->at(menuCKey));
							int buttonCKey = -1;
							for (int k = 0; k < menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->size(); k++)
							{
								if (menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->at(k)->Type() == "ButtonC")
								{
									buttonCKey = k;
								}
							}
							static_cast<ButtonComponent*>(menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->at(buttonCKey))->Activated(true);
							menuTimer = 0;
						}
					}
				}
				else
				{
					menuTimer++;
				}

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