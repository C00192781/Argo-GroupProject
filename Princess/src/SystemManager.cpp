#include "SystemManager.h"

void SystemManager::Update(float deltaTime)
{

	if (MovementSystem->Active()) { MovementSystem->Update(deltaTime); }
	if (ControlSystem->Active()) { ControlSystem->Update(); }

	if (RenderSystem->Active()) { RenderSystem->Update(); }
	if (AiSystems->Active()) { AiSystems->Update(deltaTime); }

	

}