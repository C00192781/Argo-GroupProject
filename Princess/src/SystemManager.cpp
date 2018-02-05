#include "SystemManager.h"

void SystemManager::Update()
{
	if (flag == false)
	{
		AiSystem->Spawn();
		flag = true;
	}
	if (MovementSystem->Active()) { MovementSystem->Update(); }
	if (ControlSystem->Active()) { ControlSystem->Update(); }
	if (RenderSystem->Active()) { RenderSystem->Update(); }
	if (AiSystem->Active()) { AiSystem->Update(); }
}