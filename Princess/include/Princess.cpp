#include "Princess.h"

Entity* Princess::CharA(std::string ID, SDL_Point pos, int personality)
{
	Entity *princess = new Entity("Princess");
	princess->AddComponent(new AiLogicComponent);
	princess->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	princess->AddComponent(new PositionComponent(pos));
	princess->AddComponent(new MovementComponent(85));
//	princess->AddComponent(new SeekComponent());
	princess->AddComponent(new AttributesComponent());
//	princess->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	int posKey = -1;
	for (int i = 0; i < princess->GetComponents()->size(); i++)
	{
		if (princess->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(princess->GetComponents()->at(posKey))->setPosition(pos);


	return princess;
}

Entity* Princess::CharB(std::string ID, SDL_Point pos, int personality)
{
	Entity *princess = new Entity("Princess");
	princess->AddComponent(new AiLogicComponent);
	princess->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	princess->AddComponent(new PositionComponent(pos));
	princess->AddComponent(new MovementComponent(100));
	princess->AddComponent(new SeekComponent());
	princess->AddComponent(new AttributesComponent());

	//princess->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	int posKey = -1;
	for (int i = 0; i < princess->GetComponents()->size(); i++)
	{
		if (princess->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(princess->GetComponents()->at(posKey))->setPosition(pos);

	return princess;
}



Entity* Princess::CharC(std::string ID, SDL_Point pos, int personality)
{
	Entity *princess = new Entity("Princess");
	princess->AddComponent(new AiLogicComponent);
	princess->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	princess->AddComponent(new PositionComponent(pos));
	princess->AddComponent(new MovementComponent(100));
	princess->AddComponent(new SeekComponent());
	princess->AddComponent(new AttributesComponent());
//	princess->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	int posKey = -1;
	for (int i = 0; i < princess->GetComponents()->size(); i++)
	{
		if (princess->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(princess->GetComponents()->at(posKey))->setPosition(pos);

	return princess;
}



Entity* Princess::CharD(std::string ID, SDL_Point pos, int personality)
{
	Entity *princess = new Entity("Princess");
	princess->AddComponent(new AiLogicComponent);
	princess->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	princess->AddComponent(new PositionComponent(pos));
	princess->AddComponent(new MovementComponent(100));
	princess->AddComponent(new SeekComponent());
	princess->AddComponent(new AttributesComponent());
	//princess->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	int posKey = -1;
	for (int i = 0; i < princess->GetComponents()->size(); i++)
	{
		if (princess->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(princess->GetComponents()->at(posKey))->setPosition(pos);

	return princess;
}

