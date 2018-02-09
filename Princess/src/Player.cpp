#include "Player.h"

Entity* Player::Player_Human1(std::string ID, SDL_Point pos, int personality)
{
	Entity *player = new Entity("player");
	player->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	player->AddComponent(new PositionComponent(pos));
	player->AddComponent(new MovementComponent(85));
	player->AddComponent(new AttributesComponent());
	//	player->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	int posKey = -1;
	for (int i = 0; i < player->GetComponents()->size(); i++)
	{
		if (player->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(player->GetComponents()->at(posKey))->setPosition(pos);


	return player;
}

Entity* Player::Player_Human2(std::string ID, SDL_Point pos, int personality)
{
	Entity *player = new Entity("player");
	player->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	player->AddComponent(new PositionComponent(pos));
	player->AddComponent(new MovementComponent(100));
	player->AddComponent(new AttributesComponent());

	//player->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	static_cast<PositionComponent*>(player->GetComponents()->back())->setPosition(pos);
	return player;
}



Entity* Player::Player_Human3(std::string ID, SDL_Point pos, int personality)
{
	Entity *player = new Entity("player");
	player->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	player->AddComponent(new PositionComponent(pos));
	player->AddComponent(new MovementComponent(100));
	player->AddComponent(new AttributesComponent());
	//	player->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	static_cast<PositionComponent*>(player->GetComponents()->back())->setPosition(pos);
	return player;
}



Entity* Player::Player_Human4(std::string ID, SDL_Point pos, int personality)
{
	Entity *player = new Entity("player");
	player->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	player->AddComponent(new PositionComponent(pos));
	player->AddComponent(new MovementComponent(100));
	player->AddComponent(new AttributesComponent());
	//player->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	static_cast<PositionComponent*>(player->GetComponents()->back())->setPosition(pos);
	return player;
}




//Entity* playerEntity(std::string ID, SDL_Point pos, int personality)
//{
//	Entity *player = new Entity("player");
//	player->AddComponent(new AiLogicComponent);
//	player->AddComponent(new SpriteComponent(ID, 0, 0, 0, 0, 32, 32, 0)); //textid
//	player->AddComponent(new PositionComponent());
//	static_cast<PositionComponent*>(player->GetComponents()->back())->setPosition(pos);
//	return player;
//}
//

Entity* Player::Player_AI1(std::string ID, SDL_Point pos, int personality)
{
	Entity *player = new Entity("player");
	player->AddComponent(new AiLogicComponent);
	player->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	player->AddComponent(new PositionComponent(pos));
	player->AddComponent(new MovementComponent(85));
	player->AddComponent(new SeekComponent());
	player->AddComponent(new AttributesComponent());
	//	player->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	int posKey = -1;
	for (int i = 0; i < player->GetComponents()->size(); i++)
	{
		if (player->GetComponents()->at(i)->Type() == "PC")
		{
			posKey = i;
		}
	}
	static_cast<PositionComponent*>(player->GetComponents()->at(posKey))->setPosition(pos);


	return player;
}

Entity* Player::Player_AI2(std::string ID, SDL_Point pos, int personality)
{
	Entity *player = new Entity("player");
	player->AddComponent(new AiLogicComponent);
	player->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	player->AddComponent(new PositionComponent(pos));
	player->AddComponent(new MovementComponent(100));
	player->AddComponent(new SeekComponent());
	player->AddComponent(new AttributesComponent());

	//player->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	static_cast<PositionComponent*>(player->GetComponents()->back())->setPosition(pos);
	return player;
}



Entity* Player::Player_AI3(std::string ID, SDL_Point pos, int personality)
{
	Entity *player = new Entity("player");
	player->AddComponent(new AiLogicComponent);
	player->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	player->AddComponent(new PositionComponent(pos));
	player->AddComponent(new MovementComponent(100));
	player->AddComponent(new SeekComponent());
	player->AddComponent(new AttributesComponent());
	//	player->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	static_cast<PositionComponent*>(player->GetComponents()->back())->setPosition(pos);
	return player;
}



Entity* Player::Player_AI4(std::string ID, SDL_Point pos, int personality)
{
	Entity *player = new Entity("player");
	player->AddComponent(new AiLogicComponent);
	player->AddComponent(new SpriteComponent(ID, 0, 1, 0, 0, 16, 16, 0)); //textid
	player->AddComponent(new PositionComponent(pos));
	player->AddComponent(new MovementComponent(100));
	player->AddComponent(new SeekComponent());
	player->AddComponent(new AttributesComponent());
	//player->AddComponent(new AttributesComponent(10, 10, 0, 0, 80, 80));
	static_cast<PositionComponent*>(player->GetComponents()->back())->setPosition(pos);
	return player;
}

