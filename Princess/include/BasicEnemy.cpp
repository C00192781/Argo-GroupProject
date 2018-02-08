#include "BasicEnemy.h"

Entity* BasicEnemy::CharA(std::string ID, SDL_Point pos, int element)
{
	Entity *BasicEnemy = new Entity("Ranged Enemy");
	BasicEnemy->AddComponent(new AiLogicComponent);
	BasicEnemy->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 16, 16, 0)); ////sprite id
	BasicEnemy->AddComponent(new PositionComponent(pos));
	BasicEnemy->AddComponent(new MovementComponent(100));
	BasicEnemy->AddComponent(new SeekComponent(600,0));
	static_cast<PositionComponent*>(BasicEnemy->GetComponents()->back())->setPosition(pos.x, pos.y);
	BasicEnemy->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	return BasicEnemy;
}

Entity* BasicEnemy::CharB(std::string ID, SDL_Point pos, int element)
{
	Entity *BasicEnemy = new Entity("Melee Enemy");
	BasicEnemy->AddComponent(new AiLogicComponent);
	BasicEnemy->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 16, 16, 0)); ////sprite id
	BasicEnemy->AddComponent(new PositionComponent(pos));
	BasicEnemy->AddComponent(new MovementComponent(100));
	BasicEnemy->AddComponent(new SeekComponent(800,800));
	BasicEnemy->AddComponent(new AttackComponent(1, 1, 1));
	static_cast<PositionComponent*>(BasicEnemy->GetComponents()->back())->setPosition(pos.x, pos.y);
	BasicEnemy->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	return BasicEnemy;
}



Entity* BasicEnemy::CharC(std::string ID, SDL_Point pos, int element)
{
	Entity *BasicEnemy = new Entity("Spellcaster Enemy");
	BasicEnemy->AddComponent(new AiLogicComponent);
	BasicEnemy->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 16, 16, 0)); ////sprite id
	BasicEnemy->AddComponent(new PositionComponent(pos));
	//BasicEnemy->AddComponent(new MovementComponent(100));
	//BasicEnemy->AddComponent(new SeekComponent(100,100));
	static_cast<PositionComponent*>(BasicEnemy->GetComponents()->back())->setPosition(pos.x, pos.y);
	BasicEnemy->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));

	return BasicEnemy;
}



Entity* BasicEnemy::CharD(std::string ID, SDL_Point pos, int element)
{
	Entity *BasicEnemy = new Entity("Basic Enemy");
	BasicEnemy->AddComponent(new AiLogicComponent);
	BasicEnemy->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 16, 16, 0)); //sprite id
	BasicEnemy->AddComponent(new PositionComponent(pos));
	BasicEnemy->AddComponent(new MovementComponent(100));
	BasicEnemy->AddComponent(new SeekComponent(500,550));
	static_cast<PositionComponent*>(BasicEnemy->GetComponents()->back())->setPosition(pos.x, pos.y);
	BasicEnemy->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
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
