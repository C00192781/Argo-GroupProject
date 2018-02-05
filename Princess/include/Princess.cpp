#include "Princess.h"

Entity* Princess::CharA(std::string ID, SDL_Point pos, int personality)
{
	Entity *princess = new Entity("Princess");
	princess->AddComponent(new AiLogicComponent);
	princess->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	princess->AddComponent(new PositionComponent(SDL_Point{ 200,200 }));
	princess->AddComponent(new MovementComponent(60));
	princess->AddComponent(new SeekComponent());
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
