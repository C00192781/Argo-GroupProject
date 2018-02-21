#pragma once
#include "System.h"
#include "AttributesMomento.h"
#include "AttributesComponent.h"
#include "StateManager.h"


class MementoCaretaker : public System
{
public:
	MementoCaretaker(StateManager * states);
	~MementoCaretaker();

	void LoadComponent();
	void UnloadComponent(int x);

	void Update();

	void RestoreStateAttributesMemento(std::string entityID);
	void SaveStateAttributesMemento(std::string entityID);

private:
	StateManager* m_states;
};