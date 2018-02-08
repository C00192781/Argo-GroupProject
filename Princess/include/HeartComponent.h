#ifndef _HEARTCOMPONENT_H
#define _HEARTCOMPONENT_H
#include <list>
#include "Component.h"

enum HeartState
{
	EMPTY,
	HALF,
	FULL
};

enum class HeartTypes
{
	HEALTH,
	ARMOUR
};

class HeartComponent : public Component
{
public:
	HeartComponent(std::vector<Entity*>* heartVector)
	{
		m_type = "HC";
		m_index = -1;
		m_state = HeartState::FULL;
		m_heartType = HeartTypes::HEALTH;
		m_heartVector = heartVector;
	};
	~HeartComponent() {};

	int Index() { return m_index; };
	void Index(int index) { m_index = index; };

	int State() { return m_state; };
	void State(int state) { m_state = state; };

	HeartTypes HeartType() { return m_heartType; };
	void HeartType(HeartTypes heartType) { m_heartType = heartType; };

	std::vector<Entity*>* HeartList() { return m_heartVector; };
	//void HeartList(std::list<HeartComponent>* heartList) { m_heartList = heartList; };

private:

	int m_index;
	int m_state;
	HeartTypes m_heartType;
	std::vector<Entity*>* m_heartVector;

};

#endif
