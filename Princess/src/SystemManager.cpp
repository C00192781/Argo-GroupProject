#include "SystemManager.h"

void SystemManager::Update()
{
	/*if (flag == false)
	{
		AiSystem->Spawn();
		flag = true;
	}
*/
	//auto m_entities = AiSystem->getEntities();

	if (MovementSystem->Active()) { MovementSystem->Update(); }
	if (ControlSystem->Active()) { ControlSystem->Update(); }

	//RenderSystem->addEntities(m_entities);

	if (RenderSystem->Active()) { RenderSystem->Update(); }
	if (AiSystem->Active()) { AiSystem->Update(); }

}