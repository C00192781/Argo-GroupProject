#include "WorldTileFactory.h"

Entity* WorldTileFactory::Planes(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Planes");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 0));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
Entity* WorldTileFactory::Meadow(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Meadow");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 1, 0, 16, 16, 0));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
Entity* WorldTileFactory::Forest(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Forest");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 2, 0, 16, 16, 0));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}

Entity* WorldTileFactory::Desert(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Desert");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 1));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
Entity* WorldTileFactory::Dunes(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Dunes");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 1, 0, 16, 16, 1));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
Entity* WorldTileFactory::Rock(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Rock");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 2, 0, 16, 16, 1));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}

Entity* WorldTileFactory::SnowField(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("SnowField");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 0, 0, 16, 16, 2));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
Entity* WorldTileFactory::SnowDunes(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("SnowDunes");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 1, 0, 16, 16, 2));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
Entity* WorldTileFactory::Glacier(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Glacier");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 2, 0, 16, 16, 2));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}

Entity* WorldTileFactory::Water(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("Water");
	holder->AddComponent(new SpriteComponent(textureID, 0, 1, 0, 0, 16, 16, 3));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}
Entity* WorldTileFactory::IceSheet(std::string textureID, int x, int y)
{
	Entity *holder = new Entity("IceSheet");
	holder->AddComponent(new SpriteComponent(textureID, 0, 0, 2, 0, 16, 16, 3));
	holder->AddComponent(new PositionComponent());
	static_cast<PositionComponent*>(holder->GetComponents()->back())->setPosition(SDL_Point{ x,y });
	holder->Active(true);
	return holder;
}