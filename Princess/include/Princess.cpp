#include "Princess.h"

Entity* Princess::CharA(std::string ID, SDL_Point pos, int personality)
{
	Entity *princess = new Entity("Princess");
	princess->AddComponent(new AiLogicComponent);
	princess->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	princess->AddComponent(new PositionComponent(pos));
	princess->AddComponent(new MovementComponent(85));
	princess->AddComponent(new SeekComponent());
	princess->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	static_cast<PositionComponent*>(princess->GetComponents()->back())->setPosition(pos);
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
	princess->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	static_cast<PositionComponent*>(princess->GetComponents()->back())->setPosition(pos);
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
	princess->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	static_cast<PositionComponent*>(princess->GetComponents()->back())->setPosition(pos);
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
	princess->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	static_cast<PositionComponent*>(princess->GetComponents()->back())->setPosition(pos);
	return princess;
}




//Entity* PrincessEntity(std::string ID, SDL_Point pos, int personality)
//{
//	Entity *princess = new Entity("Princess");
//	princess->AddComponent(new AiLogicComponent);
//	princess->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 32, 32, 0)); //textid
//	princess->AddComponent(new PositionComponent());
//	static_cast<PositionComponent*>(princess->GetComponents()->back())->setPosition(pos);
//	return princess;
//}
//
