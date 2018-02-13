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

	activated1 = false;
	activated2 = false;
	activated3 = false;
	activated4 = false;
	activated5 = false;
	activated6 = false;
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
