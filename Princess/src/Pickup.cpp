#include "Pickup.h"

Entity* Pickup::PickupA(std::string ID, SDL_Point pos, int value)
{
	Entity *Pickup = new Entity("Chocolate");
	Pickup->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 31, 31, 0)); ////sprite id 
	Pickup->AddComponent(new CollisionComponent(pos.x, pos.y, 31, 31, 2));
	Pickup->AddComponent(new PositionComponent(pos));
	Pickup->AddComponent(new CurrencyComponent(value));

	int posKey = -1;
	for (int i = 0; i < Pickup->GetComponents()->size(); i++)
	{
		if (Pickup->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(Pickup->GetComponents()->at(posKey))->setPosition(pos.x, pos.y);


	return Pickup;
}

Entity* Pickup::PickupB(std::string ID, SDL_Point pos, int value)
{
	Entity *Pickup = new Entity("Jewels");
	Pickup->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 31, 31, 0)); ////sprite id 
	Pickup->AddComponent(new CollisionComponent(pos.x, pos.y, 31, 31, 2));
	Pickup->AddComponent(new PositionComponent(pos));
	Pickup->AddComponent(new CurrencyComponent(value));
	//	Pickup->AddComponent(new eHPComp());

	int posKey = -1;
	for (int i = 0; i < Pickup->GetComponents()->size(); i++)
	{
		if (Pickup->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(Pickup->GetComponents()->at(posKey))->setPosition(pos.x, pos.y);

	return Pickup;
}



Entity* Pickup::PickupC(std::string ID, SDL_Point pos, int value)
{
	Entity *Pickup = new Entity("Gold");
	Pickup->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 31, 31, 0)); ////sprite id 
	Pickup->AddComponent(new CollisionComponent(pos.x, pos.y, 31, 31, 2));
	Pickup->AddComponent(new PositionComponent(pos));
	Pickup->AddComponent(new CurrencyComponent(value));
	//	Pickup->AddComponent(new eHPComp());

	int posKey = -1;
	for (int i = 0; i < Pickup->GetComponents()->size(); i++)
	{
		if (Pickup->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(Pickup->GetComponents()->at(posKey))->setPosition(pos.x, pos.y);

	return Pickup;
}



Entity* Pickup::PickupD(std::string ID, SDL_Point pos, int value)
{
	Entity *Pickup = new Entity("Literature");
	Pickup->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 31, 31, 0)); ////sprite id 
	Pickup->AddComponent(new CollisionComponent(pos.x, pos.y, 31, 31, 2));
	Pickup->AddComponent(new PositionComponent(pos));
	//	Pickup->AddComponent(new eHPComp());
	Pickup->AddComponent(new CurrencyComponent(value));

	int posKey = -1;
	for (int i = 0; i < Pickup->GetComponents()->size(); i++)
	{
		if (Pickup->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(Pickup->GetComponents()->at(posKey))->setPosition(pos.x, pos.y);

	return Pickup;


}

//Entity* PickupEntity(std::string ID, SDL_Point pos, int personality)
//{
//	Entity *Pickup = new Entity("Pickup");
//	Pickup->AddComponent(new AiLogicComponent);
//	Pickup->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 32, 32, 0)); //textid
//	Pickup->AddComponent(new PositionComponent());
//	static_cast<PositionComponent*>(Pickup->GetComponents()->back())->setPosition(pos);
//	return Pickup;
//}
//
