//#include "MenuSystem.h"

/*
MenuSystem::MenuSystem(EventListener * listener, StateManager * states)
{
	m_eventListener = listener;
	m_states = states;
	indexActiveMenu = -1;
	menuTimer = 0;
	clickTimer = 0;
	m_active = true;
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
	if (Active() == true)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			if (indexActiveMenu != -1 && i == indexActiveMenu)
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
							SDL_Point buttonPos = SDL_Point();
							buttonPos.x = (int)static_cast<PositionComponent*>(menu->Buttons()->at(j)->GetComponents()->at(pcKey))->getX();
							buttonPos.y = (int)static_cast<PositionComponent*>(menu->Buttons()->at(j)->GetComponents()->at(pcKey))->getY();
							SDL_Rect rect = SDL_Rect();
							rect.x = r->x + buttonPos.x;
							rect.y = r->y + buttonPos.y;
							rect.w = r->w*GAME_SCALE;
							rect.h = r->h*GAME_SCALE;
							if (SDL_PointInRect(&p, &rect) == true)
							{
								if (m_eventListener->LeftClick)
								{
									if (clickTimer > 3)
									{
										static_cast<ButtonComponent*>(menu->Buttons()->at(j)->GetComponents()->at(buttonCKey))->Activated(true);
										clickTimer = 0;
									}
									else
									{
										clickTimer++;
									}

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
										static_cast<SpriteComponent*>(menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->at(scTwoKey))->SheetX(0);

										menu->SelectedButtonIndex(j);
										//std::cout << menu->SelectedButtonIndex() << std::endl;

										static_cast<ButtonComponent*>(menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->at(buttonCKey))->Selected(true);
										static_cast<SpriteComponent*>(menu->Buttons()->at(menu->SelectedButtonIndex())->GetComponents()->at(scKey))->SheetX(1);
									}
								}
							}
						}
					}
					if (menuTimer > 10)
					{
						if (i == indexActiveMenu)
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
											static_cast<SpriteComponent*>(menu->Buttons()->at(0)->GetComponents()->at(scOneKey))->SheetX(0);

											static_cast<ButtonComponent*>(menu->Buttons()->at(menu->Buttons()->size() - 1)->GetComponents()->at(buttonCTwoKey))->Selected(true);
											static_cast<SpriteComponent*>(menu->Buttons()->at(menu->Buttons()->size() - 1)->GetComponents()->at(scTwoKey))->SheetX(1);

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
													static_cast<SpriteComponent*>(menu->Buttons()->at(j)->GetComponents()->at(scOneKey))->SheetX(0);

													static_cast<ButtonComponent*>(menu->Buttons()->at((j - 1))->GetComponents()->at(buttonTwoCKey))->Selected(true);
													static_cast<SpriteComponent*>(menu->Buttons()->at((j - 1))->GetComponents()->at(scTwoKey))->SheetX(1);

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
											static_cast<SpriteComponent*>(menu->Buttons()->at(menu->Buttons()->size() - 1)->GetComponents()->at(scTwoKey))->SheetX(0);

											static_cast<ButtonComponent*>(menu->Buttons()->at(0)->GetComponents()->at(buttonCTwoKey))->Selected(true);
											static_cast<SpriteComponent*>(menu->Buttons()->at(0)->GetComponents()->at(scOneKey))->SheetX(1);
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
													static_cast<SpriteComponent*>(menu->Buttons()->at(j)->GetComponents()->at(scOneKey))->SheetX(0);

													static_cast<ButtonComponent*>(menu->Buttons()->at((j + 1))->GetComponents()->at(buttonTwoCKey))->Selected(true);
													static_cast<SpriteComponent*>(menu->Buttons()->at((j + 1))->GetComponents()->at(scTwoKey))->SheetX(1);

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

					}
					else
					{
						menuTimer++;
					}

					for (int k = 0; k < menu->Buttons()->size(); k++)
					{
						int buttonCKey = -1;
						for (int j = 0; j < menu->Buttons()->at(k)->GetComponents()->size(); j++)
						{
							if (menu->Buttons()->at(k)->GetComponents()->at(j)->Type() == "ButtonC")
							{
								buttonCKey = j;
							}
						}
						if (buttonCKey >= 0)
						{
							if (static_cast<ButtonComponent*>(menu->Buttons()->at(k)->GetComponents()->at(buttonCKey))->Activated() == true)
							{
								static_cast<ButtonComponent*>(menu->Buttons()->at(k)->GetComponents()->at(buttonCKey))->Activated(false);
								if (menu->Buttons()->at(k)->ID() == "StartGame")
								{
									std::cout << "Start The Game" << std::endl;
									m_states->StartGame = true;
								}
								else if (menu->Buttons()->at(k)->ID() == "ExitGame")
								{
									std::cout << "Close The Application" << std::endl;
									m_states->ExitGame = true;
								}
								else if (menu->Buttons()->at(k)->ID() == "OpenOptions")
								{
									std::cout << "Open Options Menu" << std::endl;
									m_states->Options = true;
								}
								else if (menu->Buttons()->at(k)->ID() == "SoundLeft")
								{
									std::cout << "Sound Decrease" << std::endl;
									m_states->decreaseSound = true;
								}
								else if (menu->Buttons()->at(k)->ID() == "SoundRight")
								{
									std::cout << "Sound Increase" << std::endl;
									m_states->increaseSound = true;
								}
								else if (menu->Buttons()->at(k)->ID() == "MusicLeft")
								{
									std::cout << "Music Decrease" << std::endl;
									m_states->decreaseMusic = true;
								}
								else if (menu->Buttons()->at(k)->ID() == "MusicRight")
								{
									m_states->increaseMusic = true;
									std::cout << "Music Increase" << std::endl;
								}
								else if (menu->Buttons()->at(k)->ID() == "ReturnMainMenu")
								{
									std::cout << "Return To Main Menu" << std::endl;
									m_states->MainMenu = true;
								}
								else
								{

								}
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
			if (m_entities.at(i)->ID() == ID)
			{
				if (ID == "MainMenu")
				{
					indexActiveMenu = i;
					activeMenuID = "MainMenu";
					//return;
				}
				else if (ID == "OptionsMenu")
				{
					indexActiveMenu = i;
					activeMenuID = "OptionsMenu";
					//return;
				}
				else
				{
					std::cout << "Unknown ID" << std::endl;
				}
			}
		}
	}
}

void MenuSystem::SetUpMainMenu()
{
	Entity * menu = new Entity("MainMenu");
	MenuComponent * menuC = new MenuComponent();

	Entity * buttonOne = new Entity("StartGame");
	buttonOne->AddComponent(new PositionComponent(SDL_Point{ 200, 100 }));
	buttonOne->AddComponent(new SpriteComponent("StartGameButton", 2, 0, 0, 0, 128, 32, 0));
	static_cast<SpriteComponent*>(buttonOne->GetComponents()->at(1))->SheetX(1);
	buttonOne->AddComponent(new ButtonComponent(100, 100, 128, 32));


	Entity * buttonTwo = new Entity("OpenOptions");
	buttonTwo->AddComponent(new PositionComponent(SDL_Point{ 200, 300 }));
	buttonTwo->AddComponent(new SpriteComponent("OptionsButton", 2, 0, 0, 0, 128, 32, 0));
	buttonTwo->AddComponent(new ButtonComponent(100, 300, 128, 32));

	Entity * buttonThree = new Entity("ExitGame");
	buttonThree->AddComponent(new PositionComponent(SDL_Point{ 200, 500 }));
	buttonThree->AddComponent(new SpriteComponent("ExitGameButton", 2, 0, 0, 0, 128, 32, 0));
	buttonThree->AddComponent(new ButtonComponent(100, 500, 128, 32));

	menuC->Buttons()->push_back(buttonOne);
	menuC->Buttons()->push_back(buttonTwo);
	menuC->Buttons()->push_back(buttonThree);

	menu->AddComponent(menuC);
	m_entities.push_back(menu);
}

void MenuSystem::SetUpOptionsMenu()
{
	Entity * menu = new Entity("OptionsMenu");
	MenuComponent * menuC = new MenuComponent();

	Entity * buttonOne = new Entity("SoundLeft");
	buttonOne->AddComponent(new PositionComponent(SDL_Point{ 100, 100 }));
	buttonOne->AddComponent(new SpriteComponent("LeftArrowButton", 2, 0, 0, 0, 32, 32, 0));
	static_cast<SpriteComponent*>(buttonOne->GetComponents()->at(1))->IsAnimating(false);
	buttonOne->AddComponent(new ButtonComponent(100, 100, 32, 32));

	Entity * buttonTwo = new Entity("SoundRight");
	buttonTwo->AddComponent(new PositionComponent(SDL_Point{ 600, 100 }));
	buttonTwo->AddComponent(new SpriteComponent("RightArrowButton", 2, 0, 0, 0, 32, 32, 0));
	static_cast<SpriteComponent*>(buttonTwo->GetComponents()->at(1))->IsAnimating(false);
	buttonTwo->AddComponent(new ButtonComponent(600, 100, 32, 32));

	Entity * soundText = new Entity("SoundText");
	soundText->AddComponent(new PositionComponent(SDL_Point{ 325, 125 }));
	soundText->AddComponent(new TextComponent("ComicSans", "Sound :", SDL_Color{ 255,255,255,255 }, 64 * 3, 16 * 3));

	Entity * buttonThree = new Entity("MusicLeft");
	buttonThree->AddComponent(new PositionComponent(SDL_Point{ 100, 300 }));
	buttonThree->AddComponent(new SpriteComponent("LeftArrowButton", 2, 0, 0, 0, 32, 32, 0));
	static_cast<SpriteComponent*>(buttonThree->GetComponents()->at(1))->IsAnimating(false);
	buttonThree->AddComponent(new ButtonComponent(100, 300, 32, 32));

	Entity * buttonFour = new Entity("MusicRight");
	buttonFour->AddComponent(new PositionComponent(SDL_Point{ 600, 300 }));
	buttonFour->AddComponent(new SpriteComponent("RightArrowButton", 2, 0, 0, 0, 32, 32, 0));
	static_cast<SpriteComponent*>(buttonFour->GetComponents()->at(1))->IsAnimating(false);
	buttonFour->AddComponent(new ButtonComponent(600, 300, 32, 32));

	Entity * musicText = new Entity("MusicText");
	musicText->AddComponent(new PositionComponent(SDL_Point{ 325, 325 }));
	musicText->AddComponent(new TextComponent("ComicSans", "Music :", SDL_Color{ 255,255,255,255 }, 64 * 3, 16 * 3));

	Entity * buttonFive = new Entity("ReturnMainMenu");
	buttonFive->AddComponent(new PositionComponent(SDL_Point{ 200, 450 }));
	buttonFive->AddComponent(new SpriteComponent("MainMenuButton", 2, 0, 0, 0, 128, 32, 0));
	static_cast<SpriteComponent*>(buttonFive->GetComponents()->at(1))->IsAnimating(false);
	buttonFive->AddComponent(new ButtonComponent(200, 450, 128, 32));

	menuC->Buttons()->push_back(buttonOne);
	menuC->Buttons()->push_back(buttonTwo);
	menuC->Buttons()->push_back(buttonThree);
	menuC->Buttons()->push_back(buttonFour);
	menuC->Buttons()->push_back(buttonFive);
	menuC->Buttons()->push_back(soundText);
	menuC->Buttons()->push_back(musicText);

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
	std::vector<Entity*>::iterator it = m_entities.begin();
	while (it != m_entities.end())
	{
		if ((*it)->ID() == ID)
		{
			it = m_entities.erase((it));
		}
		else
		{
			it++;
		}
		
	}
	std::cout << "Finished";
	//for (std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end() ; ++it)
	//{

	//}


}

MenuComponent * MenuSystem::GetMenuComponent(std::string ID)
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (m_entities.at(i)->ID() == ID)
		{
			int menuCKey = -1;
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "MenuC")
				{
					menuCKey = j;
				}
			}
			if (menuCKey >= 0)
			{
				return static_cast<MenuComponent*>(m_entities.at(i)->GetComponents()->at(menuCKey));
			}
			else
			{
				std::cout << "ERROR MENU COMPONENT NOT FOUND" << std::endl;
				return new MenuComponent();
			}
		}
	}
}



void MenuSystem::LoadComponent()
{

}

void MenuSystem::UnloadComponent(int x)
{

}
*/