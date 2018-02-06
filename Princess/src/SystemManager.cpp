#include "SystemManager.h"

void SystemManager::Update(float deltaTime)
{

	if (MovementSystem->Active()) { MovementSystem->Update(deltaTime); }
	if (ControlSystem->Active()) { ControlSystem->Update(); }

	if (RenderSystem->Active()) { RenderSystem->Update(); }
	if (AiSystem->Active()) { AiSystem->Update(deltaTime); }

	if (healthSystem->Active()) { healthSystem->Update(deltaTime); }

}