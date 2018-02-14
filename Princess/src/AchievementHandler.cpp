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
	json achievement;
	std::ifstream achievement_file("Achievements.json", std::ifstream::binary);
	achievement_file >> achievement;

	std::cout << achievement["achievement1"] << std::endl;

	activated1 = achievement["achievement1"];
	activated2 = achievement["achievement2"];
	activated3 = achievement["achievement3"];
	activated4 = achievement["achievement4"];
	activated5 = achievement["achievement5"];
	activated6 = achievement["achievement6"];

	j["achievement1"] = achievement["achievement1"];
	j["achievement2"] = achievement["achievement2"];
	j["achievement3"] = achievement["achievement3"];
	j["achievement4"] = achievement["achievement4"];
	j["achievement5"] = achievement["achievement5"];
	j["achievement6"] = achievement["achievement6"];

	// write to JSON file
	std::ofstream o("Achievements.json");
	//o << std::setw(6) << j << std::endl;
	o << j << std::endl;
}

void AchievementHandler::HandleAchievements()
{
	//std::cout << m_systemManager->ControlSystem->totalMovement << std::endl;
	if (m_systemManager->ControlSystem->totalMovement >= 1000 && activated1 == false)
	{	
		subject.AttachObserver(&observers[0]);
		subject.DetachObserver(&observers[1]);
		subject.DetachObserver(&observers[2]);
		subject.DetachObserver(&observers[3]);
		subject.DetachObserver(&observers[4]);
		subject.DetachObserver(&observers[5]);

		subject.ChangeStatus(true);
		activated1 = true;

		j["achievement1"] = activated1;
		std::ofstream o("Achievements.json");
		o << j << std::endl;

	}

	//if (m_achievementListener->achievement1 == true && activated1 == false)
	//{
	//	subject.AttachObserver(&observers[0]);
	//	subject.DetachObserver(&observers[1]);
	//	subject.DetachObserver(&observers[2]);
	//	subject.DetachObserver(&observers[3]);
	//	subject.DetachObserver(&observers[4]);
	//	subject.DetachObserver(&observers[5]);

	//	subject.ChangeStatus(true);
	//	activated1 = true;
	//}
	//if (m_achievementListener->achievement2 == true && activated2 == false)
	//{
	//	subject.DetachObserver(&observers[0]);
	//	subject.AttachObserver(&observers[1]);
	//	subject.DetachObserver(&observers[2]);
	//	subject.DetachObserver(&observers[3]);
	//	subject.DetachObserver(&observers[4]);
	//	subject.DetachObserver(&observers[5]);

	//	subject.ChangeStatus(true);
	//	activated2 = true;
	//}
	//if (m_achievementListener->achievement3 == true && activated3 == false)
	//{
	//	subject.DetachObserver(&observers[0]);
	//	subject.DetachObserver(&observers[1]);
	//	subject.AttachObserver(&observers[2]);
	//	subject.DetachObserver(&observers[3]);
	//	subject.DetachObserver(&observers[4]);
	//	subject.DetachObserver(&observers[5]);

	//	subject.ChangeStatus(true);
	//	activated3 = true;
	//}
	//if (m_achievementListener->achievement4 == true && activated4 == false)
	//{
	//	subject.DetachObserver(&observers[0]);
	//	subject.DetachObserver(&observers[1]);
	//	subject.DetachObserver(&observers[2]);
	//	subject.AttachObserver(&observers[3]);
	//	subject.DetachObserver(&observers[4]);
	//	subject.DetachObserver(&observers[5]);

	//	subject.ChangeStatus(true);
	//	activated4 = true;
	//}
	//if (m_achievementListener->achievement5 == true && activated5 == false)
	//{
	//	subject.DetachObserver(&observers[0]);
	//	subject.DetachObserver(&observers[1]);
	//	subject.DetachObserver(&observers[2]);
	//	subject.DetachObserver(&observers[3]);
	//	subject.AttachObserver(&observers[4]);
	//	subject.DetachObserver(&observers[5]);

	//	subject.ChangeStatus(true);
	//	activated5 = true;
	//}
	//if (m_achievementListener->achievement6 == true && activated6 == false)
	//{
	//	subject.DetachObserver(&observers[0]);
	//	subject.DetachObserver(&observers[1]);
	//	subject.DetachObserver(&observers[2]);
	//	subject.DetachObserver(&observers[3]);
	//	subject.DetachObserver(&observers[4]);
	//	subject.AttachObserver(&observers[5]);

	//	subject.ChangeStatus(true);
	//	activated6 = true;
	//}
}
