#include "AchievementHandler.h"

AchievementHandler::AchievementHandler()
{

}

void AchievementHandler::Init()
{
	// we have achievements wanting to keep an updated status
	ConcreteObserver achievement1("Achievement 1");
	ConcreteObserver achievement2("Achievement 2");
	ConcreteObserver achievement3("Achievement 3");
	ConcreteObserver achievement4("Achievement 4");
	ConcreteObserver achievement5("Achievement 5");
	ConcreteObserver achievement6("Achievement 6");

	observers.push_back(achievement1);
	observers.push_back(achievement2);
	observers.push_back(achievement3);
	observers.push_back(achievement4);
	observers.push_back(achievement5);
	observers.push_back(achievement6);

	// Read from JSON file
	json jAchievement;
	std::ifstream achievement_file("Achievements.json", std::ifstream::binary);
	achievement_file >> jAchievement;

	std::cout << "First achievement is " << jAchievement["achievement1"] << std::endl;


	// If the player has triggered an achievement in a previous playthrough
	// we keep track of this using JSON
	// initialize initial values with values from previous play session
	A1.activated = jAchievement["achievement1"];
	A2.activated = jAchievement["achievement2"];
	A3.activated = jAchievement["achievement3"];
	A4.activated = jAchievement["achievement4"];
	A5.activated = jAchievement["achievement5"];
	A6.activated = jAchievement["achievement6"];

	j["achievement1"] = jAchievement["achievement1"];
	j["achievement2"] = jAchievement["achievement2"];
	j["achievement3"] = jAchievement["achievement3"];
	j["achievement4"] = jAchievement["achievement4"];
	j["achievement5"] = jAchievement["achievement5"];
	j["achievement6"] = jAchievement["achievement6"];

	// write to JSON file
	std::ofstream o("Achievements.json");
	o << j << std::endl;
}

void AchievementHandler::HandleAchievements()
{
	if (m_systemManager->controlSystem->getTotalPlayerMovement() >= 500)
	{
		static float startTime = SDL_GetTicks();
		if (A1.activated == false)
		{
			subject.AttachObserver(&observers[0]);
			subject.DetachObserver(&observers[1]);
			subject.DetachObserver(&observers[2]);
			subject.DetachObserver(&observers[3]);
			subject.DetachObserver(&observers[4]);
			subject.DetachObserver(&observers[5]);

			subject.ChangeStatus(true);
			A1.activated = true;

			j["achievement1"] = A1.activated;
			std::ofstream o("Achievements.json");
			o << j << std::endl;

			Generate("Achievement");
		}
		else
		{
			Removal("Achievement", startTime);
		}

	}
	if (m_systemManager->controlSystem->getTotalPlayerMovement() >= 1000)
	{
		static float startTime = SDL_GetTicks();
		if (A2.activated == false)
		{
			subject.DetachObserver(&observers[0]);
			subject.AttachObserver(&observers[1]);
			subject.DetachObserver(&observers[2]);
			subject.DetachObserver(&observers[3]);
			subject.DetachObserver(&observers[4]);
			subject.DetachObserver(&observers[5]);

			subject.ChangeStatus(true);
			A2.activated = true;

			j["achievement2"] = A2.activated;
			std::ofstream o("Achievements.json");
			o << j << std::endl;

			Generate("Achievement2");
		}
		else
		{
			Removal("Achievement2", startTime);
		}
	
	}
}

void AchievementHandler::Removal(std::string identifier, float startTime)
{
	if (displayQueue.size() > 0)
	{
		if (displayQueue.at(0)->ID() == identifier)
		{
			uint32_t tickTime = SDL_GetTicks();

			uint32_t lastTickTime = tickTime - startTime;
			/*uint32_t lastTickTimeInSeconds = lastTickTime * 0.001f;*/
			if (lastTickTime > 5000)
			{
				if (displayQueue.at(0)->ID() == identifier)
				{
					Replace();
				}
			}
		}
	}
}

void AchievementHandler::Replace()
{
	if (displayQueue.size() > 0)
	{
		m_systemManager->renderSystem->RemoveEntity(displayQueue.back()->ID());
		displayQueue.erase(displayQueue.begin());
	}
}

void AchievementHandler::Generate(std::string identifier)
{
	Entity *AchievementEntity = new Entity(identifier);;
	SpriteComponent * sprite = new SpriteComponent(identifier, 2, 0, 0, 0, 148, 32, 0);
	sprite->Relative(true);
	AchievementEntity->AddComponent(sprite);
	AchievementEntity->Transient(true);
	AchievementEntity->AddComponent(new PositionComponent(SDL_Point{ 0, 535 }));

	Replace();

	m_systemManager->renderSystem->AddEntity(AchievementEntity);
	displayQueue.push_back(AchievementEntity);
}



void AchievementHandler::Animate(PositionComponent *positionComponent)
{

	/*Vector2f position;
	position.X = positionComponent->getX();
	position.Y = positionComponent->getY();
	positionComponent->setPosition(position.X, position.Y);*/

}
