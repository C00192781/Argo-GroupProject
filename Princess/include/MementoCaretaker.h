#pragma once
#include "System.h"
#include "AttributesMomento.h"
#include "AttributesComponent.h"
#include "CurrencyMomento.h"
#include "CurrencyComponent.h"
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
	void RestoreStateCurrencyMemento(std::string entityID);
	void SaveStateCurrencyMemento(std::string entityID);
	

private:
	StateManager* m_states;
};