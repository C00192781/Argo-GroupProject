#include "BasicEnemy.h"

Entity* BasicEnemy::CharA(std::string ID, SDL_Point pos, int element)
{
	Entity *BasicEnemy = new Entity("Melee Enemy");
	BasicEnemy->AddComponent(new AiLogicComponent);
	BasicEnemy->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 16, 16, 0)); ////sprite id 
	BasicEnemy->AddComponent(new PositionComponent(pos));
	BasicEnemy->AddComponent(new MovementComponent(100));
	BasicEnemy->AddComponent(new SeekComponent(-50, -50));
	BasicEnemy->AddComponent(new AttackComponent(100, 1, 1));
	BasicEnemy->AddComponent(new AttributesComponent());

	int posKey = -1;
	for (int i = 0; i < BasicEnemy->GetComponents()->size(); i++)
	{
		if (BasicEnemy->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(BasicEnemy->GetComponents()->at(posKey))->setPosition(pos.x, pos.y);

	return BasicEnemy;
}

Entity* BasicEnemy::CharB(std::string ID, SDL_Point pos, int element)
{
	Entity *BasicEnemy = new Entity("Ranged Enemy");
	BasicEnemy->AddComponent(new AiLogicComponent);
	BasicEnemy->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 16, 16, 0)); ////sprite id 
	BasicEnemy->AddComponent(new PositionComponent(pos));
	BasicEnemy->AddComponent(new MovementComponent(100));
	BasicEnemy->AddComponent(new SeekComponent(-50, -50));
	BasicEnemy->AddComponent(new AttackComponent(100, 1, 1));
	BasicEnemy->AddComponent(new AttributesComponent());

	int posKey = -1;
	for (int i = 0; i < BasicEnemy->GetComponents()->size(); i++)
	{
		if (BasicEnemy->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(BasicEnemy->GetComponents()->at(posKey))->setPosition(pos.x, pos.y);

	return BasicEnemy;
}



Entity* BasicEnemy::CharC(std::string ID, SDL_Point pos, int element)
{
	Entity *BasicEnemy = new Entity("Spellcaster Enemy");
	BasicEnemy->AddComponent(new AiLogicComponent);
	BasicEnemy->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 16, 16, 0)); ////sprite id 
	BasicEnemy->AddComponent(new CollisionComponent(pos.x, pos.y, 16, 16, 2));
	BasicEnemy->AddComponent(new PositionComponent(pos));
	BasicEnemy->AddComponent(new MovementComponent());
	BasicEnemy->AddComponent(new SeekComponent(-50, -50));
	BasicEnemy->AddComponent(new AttackComponent(100, 1, 1));
	BasicEnemy->AddComponent(new AttributesComponent(26, 26, 10, 10, 100, 100));

	int posKey = -1;
	for (int i = 0; i < BasicEnemy->GetComponents()->size(); i++)
	{
		if (BasicEnemy->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(BasicEnemy->GetComponents()->at(posKey))->setPosition(pos.x, pos.y);

	return BasicEnemy;
}



Entity* BasicEnemy::CharD(std::string ID, SDL_Point pos, int element)
{
	Entity *BasicEnemy = new Entity("Basic Enemy");
	BasicEnemy->AddComponent(new AiLogicComponent);
	BasicEnemy->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 16, 16, 0)); ////sprite id 
	BasicEnemy->AddComponent(new PositionComponent(pos));
	BasicEnemy->AddComponent(new MovementComponent(100));
	BasicEnemy->AddComponent(new SeekComponent(-50, -50));
	BasicEnemy->AddComponent(new AttackComponent(100, 1, 1));
	BasicEnemy->AddComponent(new AttributesComponent());

	int posKey = -1;
	for (int i = 0; i < BasicEnemy->GetComponents()->size(); i++)
	{
		if (BasicEnemy->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(BasicEnemy->GetComponents()->at(posKey))->setPosition(pos.x, pos.y);

	return BasicEnemy;
}




//Entity* BasicEnemyEntity(std::string ID, SDL_Point pos, int personality)
//{
//	Entity *BasicEnemy = new Entity("BasicEnemy");
//	BasicEnemy->AddComponent(new AiLogicComponent);
//	BasicEnemy->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 32, 32, 0)); //textid
//	BasicEnemy->AddComponent(new PositionComponent());
//	static_cast<PositionComponent*>(BasicEnemy->GetComponents()->back())->setPosition(pos);
//	return BasicEnemy;
//}
//