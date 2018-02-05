#include "SystemManager.h"

void SystemManager::Update()
{
	if (MovementSystem->Active()) { MovementSystem->Update(); }
	if (ControlSystem->Active()) { ControlSystem->Update(); }
	if (RenderSystem->Active()) { RenderSystem->Update(); }
	if (AttackSystem->Active()) { AttackSystem->Update(); }
}