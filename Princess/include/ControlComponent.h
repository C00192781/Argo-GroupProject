#pragma once

#include "Component.h"
#include "InputHandler.h"

class ControlComponent : public Component
{
public:
	ControlComponent(InputHandler *input) 
	{ 
		m_type = "control";
		m_input = input;
	}
	
	InputHandler* getInput() { return m_input; }

private:
	InputHandler* m_input;
};