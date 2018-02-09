#include "ControlSystem.h"
#include <iostream>

void ControlSystem::Update()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		int mcKey = -1;
		int pjKey = -1;
		int playerKey = -1;
		int acKey = -1;
		int menuCKey = -1;
		// looks for if there is a movement component in the entity
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
		{
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "movement")
				{
					mcKey = j;
				}
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PJ")
				{
					pjKey = j;
				}
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "MenuC")
				{
					menuCKey = j;
				}
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC" && m_entities.at(i)->ID() == "Player")
				{
					playerKey = j;
					if (m_entities.at(i)->GetComponents()->at(j)->Type() == "AC")
					{
						acKey = j;
					}
				}
			}
			if (menuCKey >= 0)
			{
				if (menuTimer > 2)
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
				else
				{
					menuTimer++;
				}

			}
			if (playerKey >= 0)
			{
				playerPos = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(playerKey))->getPosition();
			}
			// makes sure it finds a movement component in the entity
			if (mcKey >= 0 && acKey >=0)
			{
				SDL_Point holder{ 0, 0 };
				int speed = static_cast<AttributesComponent*>(m_entities.at(i)->GetComponents()->at(acKey))->MovementSpeed();

				if (m_eventListener->W)
				{
					holder.y = -speed;
				}
				if (m_eventListener->A)
				{
					holder.x = -speed;
				}
				if (m_eventListener->S)
				{
					holder.y = speed;
				}
				if (m_eventListener->D)
				{
					holder.x = speed;
				}

				static_cast<MovementComponent*>(m_entities.at(i)->GetComponents()->at(mcKey))->setVelocity(holder);
			}
		}
		if (m_projectiles != nullptr)
		{
			for (int i = 0; i < m_projectiles->size(); i++)
			{
				int mcKey = -1;
				int pjKey = -1;
				int pcKey = -1;

				// looks for if there is a movement component in the entity
				for (int j = 0; j < m_projectiles->at(i)->GetComponents()->size(); j++)
				{
					for (int j = 0; j < m_projectiles->at(i)->GetComponents()->size(); j++)
					{
						if (m_projectiles->at(i)->GetComponents()->at(j)->Type() == "movement")
						{
							mcKey = j;
						}
						if (m_projectiles->at(i)->GetComponents()->at(j)->Type() == "PJ")
						{
							pjKey = j;
						}
						if (m_projectiles->at(i)->GetComponents()->at(j)->Type() == "PC")
						{
							pcKey = j;
						}
					}
				}
				if (m_eventListener->LeftClick == true)
				{
					lastTickTime = tickTime;
					shoot = true;
				}
				if (m_eventListener->LeftClick == false)
				{

					SDL_GetMouseState(&x, &y);
					float cosA = atan2(y - playerPos.y, x - playerPos.x) + 3.14159265359 / 180 * 90;
					if (pjKey >= 0 && pcKey >= 0)
					{
						tickTime = SDL_GetTicks();

						uint32_t difference;
						difference = tickTime - lastTickTime;

						float differenceInSeconds;
						differenceInSeconds = (float)difference * 0.001f;

						if (difference > 50 && shoot == true)
						{
							index++;
							shoot = false;
							if (index >= m_projectiles->size())
							{
								index = 0;
							}
							if (static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->getType() == "Player")
							{
								static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setAliveStatus(true);
								static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setButtonPressTime(differenceInSeconds);
								static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setOrientation(cosA);
								static_cast<PositionComponent*>(m_projectiles->at(index)->GetComponents()->at(pcKey))->setPosition(playerPos);
								//static_cast<ProjectileComponent*>(m_projectiles->at(index)->GetComponents()->at(pjKey))->setMaxSpeed(15.0f);
							}
						}
					}
				}

			}
		}
	}
}