#ifndef _HEARTMANAGERCOMPONENT_H
#define _HEARTMANAGERCOMPONENT_H
#include "Component.h"
#include "Entity.h"
#include "HeartComponent.h"

class HeartManagerComponent : public Component
{
public:
	HeartManagerComponent(HeartTypes HeartType)
	{
		m_HeartType = HeartType;
		m_hearts = new std::vector<Entity*>();
		m_type = "HMC";
	};
	~HeartManagerComponent() { delete m_hearts; };

	HeartTypes HeartType() { return m_HeartType; };
	void HeartType(HeartTypes heartType) { m_HeartType = heartType; };

	std::vector<Entity*>* HeartsVector() { return m_hearts; };
	void HeartsVector(std::vector<Entity*>* heartVector) { m_hearts = heartVector; };

private:
	HeartTypes m_HeartType;
	std::vector<Entity*>* m_hearts;
};



#endif