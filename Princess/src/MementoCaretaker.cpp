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
		}
	}
	if (m_states->LoadGame)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			RestoreStateAttributesMemento(m_entities.at(i)->ID());
		}
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
