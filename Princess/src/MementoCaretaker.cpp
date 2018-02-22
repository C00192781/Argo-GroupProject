#include "MementoCaretaker.h"


MementoCaretaker::MementoCaretaker(StateManager * states)
{
	m_states = states;
}

MementoCaretaker::~MementoCaretaker()
{

}

void MementoCaretaker::LoadComponent()
{

}

void MementoCaretaker::UnloadComponent(int x)
{

}

void MementoCaretaker::Update()
{
	if (m_states->SaveGame)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			SaveStateAttributesMemento(m_entities.at(i)->ID());
			SaveStateCurrencyMemento(m_entities.at(i)->ID());
		}
		m_states->SaveGame = false;
	}
	if (m_states->LoadGame)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			RestoreStateAttributesMemento(m_entities.at(i)->ID());
			RestoreStateCurrencyMemento(m_entities.at(i)->ID());
		}
		m_states->LoadGame = false;
	}
}

void MementoCaretaker::RestoreStateAttributesMemento(std::string entityID)
{
	if (nullptr != FindEntity(entityID)->FindComponent("attribute"))
	{
		static_cast<AttributesComponent*>(FindEntity(entityID)->FindComponent("attribute"))->Revert();
	}
}

void MementoCaretaker::SaveStateAttributesMemento(std::string entityID)
{
	if (nullptr != FindEntity(entityID)->FindComponent("attribute"))
	{
		static_cast<AttributesComponent*>(FindEntity(entityID)->FindComponent("attribute"))->Save();
	}
}

void MementoCaretaker::RestoreStateCurrencyMemento(std::string entityID)
{
	if (nullptr != FindEntity(entityID)->FindComponent("currency"))
	{
		static_cast<CurrencyComponent*>(FindEntity(entityID)->FindComponent("currency"))->Revert();
	}
}

void MementoCaretaker::SaveStateCurrencyMemento(std::string entityID)
{
	if (nullptr != FindEntity(entityID)->FindComponent("currency"))
	{
		static_cast<CurrencyComponent*>(FindEntity(entityID)->FindComponent("currency"))->Save();
	}
}