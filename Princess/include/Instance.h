#ifndef _INSTANCE_H
#define _INSTANCE_H

#include <string>
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "MovementSystem.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "GrassTileFactory.h"
#include "StateManager.h"
#include "Entity.h"
#include "stdafx.h"

class Instance
{
public:
	Instance() {};
	~Instance() {};

	virtual void Update() = 0;
	virtual void Render() = 0;

	std::string ID() { return m_id; };

protected:
	std::string m_id;

	std::vector<Entity*> m_entities;

	RenderSystem * m_renderSystem;
	MovementSystem * m_movementSystem;
	ControlSystem * m_controlSystem;

	TileFactory * m_factory;

	StateManager * m_stateManager;
};
#endif
