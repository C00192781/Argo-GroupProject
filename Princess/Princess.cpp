#include "Princess.h"

Entity* PrincessEntity(std::string ID, SDL_Point pos, int personality)
{
	Entity *princessA = new Entity("Princess");
	princessA->AddComponent(new AiLogicComponent);
	princessA->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 16, 16, 0)); //textid
	princessA->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(princessA->GetComponents()->back())->setPosition(pos);
	return holder;
}

Entity* Princess::GroundB(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Dirt Holes");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 1));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x, y });
	return holder;
}

Entity* Princess::GroundC(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Flowers");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 2));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x, y });
	return holder;
}

Entity* Princess::GroundD(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Dirt");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 3));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x, y });
	return holder;
}