#include "ControlSystem.h"
#include "PositionComponent.h"
#include <iostream>

void ControlSystem::Update(SDL_Event *e) {
	for (int i = 0; i < m_entities.size(); i++) {
		int pcKey = -1;
		int ccKey = -1;

		// looks for if there is a position and control component in the entity
		for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++) {
			for (int j = 0; j < m_entities.at(i)->GetComponents()->size(); j++)
			{
				if (m_entities.at(i)->GetComponents()->at(j)->Type() == "PC")
				{
					pcKey = j;
				}
				else if (m_entities.at(i)->GetComponents()->at(j)->Type() == "control")
				{
					ccKey = j;
				}
			}
		}

		// makes sure it finds the position in the vector of the position and control components
		if (pcKey >= -1 && ccKey >= -1) {
			SDL_Point holder = static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->getPosition();

			static_cast<ControlComponent*>(m_entities.at(i)->GetComponents()->at(ccKey))->getInput()->handleInput(*e, holder);

			static_cast<PositionComponent*>(m_entities.at(i)->GetComponents()->at(pcKey))->setPosition(holder);
		}
	}
}