#define SDL_MAIN_HANDLED

#include <iostream>
#include <time.h>
#include "Quad.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "EventListener.h"
#include "BattleMap.h"
#include "StateManager.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "ProjectileComponent.h"
#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "AttributesComponent.h"
#include "TextComponent.h"
#include "TextRenderSystem.h"
#include "ButtonComponent.h"
#include "HealthSystem.h"
#include "AISystem.h"
#include "Princess.h"
#include <chrono>
#include "SystemManager.h"
#include "InstanceManager.h"
#include "SystemManager.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "LTimer.h"
#include "AchievementHandler.h"
#include <chrono>
#include <time.h>
#include "WorldMap.h"
#include "DungeonMap.h"
#include "TownInstance.h"
#include "InstanceManager.h"
#include "AchievementHandler.h"
#include "SoundComponent.h"
#include "SoundSystem.h"
#include "AStar.h"

int GAME_SCALE = 3;

int main()
{
	SDL_Window* gameWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 816, 624, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	bool running = true;

	if (Mix_OpenAudio(22050, AUDIO_S16, 2, 1024) == -1) //Check return type
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME);
	}


	unsigned int lastTime = 0;
	float deltaTime = 0;
	unsigned int currentTime = 0;
	srand(time(NULL));

	bool debug = false;

	srand(time(NULL));

	const int SCREEN_FPS = 800;

	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };

	//The frames per second timer
	LTimer fpsTimer;

	//The frames per second cap timer
	LTimer capTimer;

	//In memory text stream
	std::stringstream timeText;

	//Start counting frames per second
	int countedFrames = 0;
	fpsTimer.start();


	ofstream myfile;
	myfile.open("Rumours.txt");
	myfile << "Claudette Perrick runs a fine alchemy shop.You should check out The Gilded Carafe.\n";
	myfile << "Amantius Allectus was killed during a burglary. They say the house was ransacked.\n";
	myfile << "Truth is, the Legion doesn't know who was behind the Emperor's murder. We've already ruled out the Dark Brotherhood. So is this something... worse?\n";
	myfile << "Sensational.\n";
	myfile << "The tide is turning, my friend. Bruma has been saved, and Martin Septim has claimed his birthright! Soon, all of Oblivion will tremble in fear!\n";
	myfile << "Have you been near Rosentia Gallenus's house recently? Smells horrible... like she left some meat out to spoil.\n";

	myfile.close();


	ResourceManager *resourceManager = new ResourceManager(gameRenderer, "Resources");

	resourceManager->AddTexture("Red", "Sprite_Red.png");
	resourceManager->AddTexture("Blue", "Sprite_Blue.png");
	resourceManager->AddTexture("Pink", "Sprite_Pink.png");
	resourceManager->AddTexture("Demon", "demon.png");
	resourceManager->AddTexture("Turf", "Turfs.png");
	resourceManager->AddTexture("Arrow", "Arrow.png");
	resourceManager->AddTexture("HeartsSheet", "heartSpriteSheet.png");
	resourceManager->AddTexture("ArmourSheet", "armourSpriteSheet.png");
	resourceManager->AddTexture("WorldTurf", "World_Turfs.png");
	resourceManager->AddTexture("Button", "Button.png");
	resourceManager->AddTexture("Pickup", "Pickup.png");

	resourceManager->AddFont("ComicSans", "ComicSans.ttf", 32);

	resourceManager->AddTexture("StartGameButton", "StartGameButton.png");
	resourceManager->AddTexture("OptionsButton", "OptionsButton.png");
	resourceManager->AddTexture("ExitGameButton", "ExitGameButton.png");

	resourceManager->AddTexture("LeftArrowButton", "LeftArrow.png");
	resourceManager->AddTexture("RightArrowButton", "RightArrow.png");
	resourceManager->AddTexture("MainMenuButton", "ReturnMainMenu.png");
	resourceManager->AddTexture("SoundText", "sound.png");
	resourceManager->AddTexture("MusicText", "music.png");

	resourceManager->AddTexture("Hearts", "Hearts.png");
	resourceManager->AddTexture("Armors", "Armors.png");

	resourceManager->AddTexture("Achievement", "PlaceholderAchievement.png");
	resourceManager->AddTexture("Achievement2", "PlaceholderAchievement2.png");

	resourceManager->AddMusic("Test", "kevin.mp3");
	resourceManager->AddMusic("Dungeon1", "Dungeon of Stuff.wav");
	resourceManager->AddMusic("Dungeon2", "Dungeon of Mystery.wav");
	resourceManager->AddMusic("Dungeon3", "FinalDungeonMusic.wav");
	resourceManager->AddMusic("Town1", "Town1.wav");
	resourceManager->AddMusic("Town2", "Town2.wav");
	resourceManager->AddMusic("Town3", "Town3.wav");
	resourceManager->AddMusic("Overworld1", "Overworld1.wav");
	resourceManager->AddMusic("Overworld2", "Overworld2.wav");
	resourceManager->AddMusic("Overworld3", "Overworld3.wav");
	resourceManager->AddMusic("TitleMusic", "TitleMusicOfDestructionTimes.wav");
	resourceManager->AddSound("Scream", "test.wav");
	resourceManager->AddSound("Placeholder", "placeholder.wav");

	resourceManager->AddTexture("Plate", "Plate.png");
	resourceManager->AddTexture("Bow", "Bow.png");
	resourceManager->AddTexture("Sword", "Sword.png");
	resourceManager->AddTexture("Wand", "Wand.png");
	resourceManager->AddTexture("Armor", "Armor.png");

	resourceManager->AddFont("munro", "munro.ttf", 32);

	Mix_AllocateChannels(6);

	AStar *aStar = new AStar();

	EventListener *listener = new EventListener();

	InputHandler *input = new InputHandler(listener, e);

	StateManager state = StateManager();

	std::vector<Entity*>* projectiles = new std::vector<Entity*>;

	SystemManager systemManager(resourceManager, gameRenderer, listener, projectiles, aStar, state);

	Entity * player = new Entity("Player");
	player->Active(true);

	systemManager.healthSystem->Active(false);

	player->AddComponent(new SpriteComponent("Red", 3, 1, 0, 0, 16, 16, 0));
	player->AddComponent(new PositionComponent(SDL_Point{ 100, 380 }));
	player->AddComponent(new AttributesComponent(20, 20, 4, 10, 100, 100));
	player->AddComponent(new MovementComponent());
	player->AddComponent(new WeaponComponent(WeaponType::RANGE));
	player->AddComponent(new NetworkIDComponent(0));
	player->AddComponent(new CollisionComponent(100, 380, 16, 16, 2));
	player->Transient(true);
	player->AddComponent(new CurrencyComponent());

	systemManager.healthSystem->AddEntity(player, "???");
	for (int i = 0; i < 12; i++)
	{
		Entity* heart = new Entity("Heart");
		heart->Transient(true);
		heart->AddComponent(new PositionComponent());
		heart->AddComponent(new SpriteComponent("Hearts", 5, 0, 0, 0, 4, 4, 0));
		static_cast<SpriteComponent*>(heart->GetComponents()->back())->Relative(true);
		systemManager.healthSystem->AddEntity(heart, "PH1");
		systemManager.renderSystem->AddEntity(heart);
	}
	for (int i = 0; i < 6; i++)
	{
		Entity* heart = new Entity("Heart");
		heart->Transient(true);
		heart->AddComponent(new PositionComponent());
		heart->AddComponent(new SpriteComponent("Armors", 5, 0, 0, 0, 4, 4, 0));
		static_cast<SpriteComponent*>(heart->GetComponents()->back())->Relative(true);
		systemManager.healthSystem->AddEntity(heart, "PH1");
		systemManager.renderSystem->AddEntity(heart);
	}

	Entity * player2 = new Entity("Player");
	player2->Active(true);
	player2->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
	player2->AddComponent(new PositionComponent(SDL_Point{ 250, 380 }));
	player2->AddComponent(new AttributesComponent(20, 20, 4, 10, 100, 100));
	player2->AddComponent(new MovementComponent());
	player2->AddComponent(new WeaponComponent(WeaponType::RANGE));
	player2->AddComponent(new CollisionComponent(250, 380, 16, 16, 2));
	//player2->AddComponent(new AiLogicComponent()); //add this if AI is to control that player2
	//player2->AddComponent(new SeekComponent()); //and this if AI is to control that player2
	player2->AddComponent(new CurrencyComponent());
	player2->AddComponent(new SoundComponent("Scream", "play", false, 1, 30, 50));
	player2->AddComponent(new MusicComponent("Test", "play", true, 0, 100));
	player2->AddComponent(new NetworkIDComponent(1));
	player2->Transient(true);

	systemManager.healthSystem->AddEntity(player2, "???");
	for (int i = 0; i < 12; i++)
	{
		Entity* heart = new Entity("Heart");
		heart->Transient(true);
		heart->AddComponent(new PositionComponent());
		heart->AddComponent(new SpriteComponent("Hearts", 5, 0, 0, 0, 4, 4, 0));
		static_cast<SpriteComponent*>(heart->GetComponents()->back())->Relative(true);
		systemManager.healthSystem->AddEntity(heart, "PH2");
		systemManager.renderSystem->AddEntity(heart);
	}
	for (int i = 0; i < 6; i++)
	{
		Entity* heart = new Entity("Heart");
		heart->Transient(true);
		heart->AddComponent(new PositionComponent());
		heart->AddComponent(new SpriteComponent("Armors", 5, 0, 0, 0, 4, 4, 0));
		static_cast<SpriteComponent*>(heart->GetComponents()->back())->Relative(true);
		systemManager.healthSystem->AddEntity(heart, "PH2");
		systemManager.renderSystem->AddEntity(heart);
	}

	Entity * player3 = new Entity("Player");
	player3->Active(true);
	player3->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
	player3->AddComponent(new PositionComponent(SDL_Point{ 300, 380 }));
	player3->AddComponent(new AttributesComponent(20, 20, 4, 10, 100, 100));
	player3->AddComponent(new MovementComponent());
	player3->AddComponent(new WeaponComponent(WeaponType::RANGE));
	player3->AddComponent(new CollisionComponent(300, 380, 16, 16, 2));
	//player3->AddComponent(new AiLogicComponent()); //add this if AI is to control that player3
	//player3->AddComponent(new SeekComponent()); //and this if AI is to control that player3
	player3->AddComponent(new CurrencyComponent());
	player3->AddComponent(new SoundComponent("Scream", "play", false, 1, 30, 50));
	player3->AddComponent(new MusicComponent("Test", "play", true, 0, 100));
	player3->AddComponent(new NetworkIDComponent(2));
	player3->Transient(true);

	systemManager.healthSystem->AddEntity(player3, "???");
	for (int i = 0; i < 12; i++)
	{
		Entity* heart = new Entity("Heart");
		heart->Transient(true);
		heart->AddComponent(new PositionComponent());
		heart->AddComponent(new SpriteComponent("Hearts", 5, 0, 0, 0, 4, 4, 0));
		static_cast<SpriteComponent*>(heart->GetComponents()->back())->Relative(true);
		systemManager.healthSystem->AddEntity(heart, "PH3");
		systemManager.renderSystem->AddEntity(heart);
	}
	for (int i = 0; i < 6; i++)
	{
		Entity* heart = new Entity("Heart");
		heart->Transient(true);
		heart->AddComponent(new PositionComponent());
		heart->AddComponent(new SpriteComponent("Armors", 5, 0, 0, 0, 4, 4, 0));
		static_cast<SpriteComponent*>(heart->GetComponents()->back())->Relative(true);
		systemManager.healthSystem->AddEntity(heart, "PH3");
		systemManager.renderSystem->AddEntity(heart);
	}


	Entity * player4 = new Entity("Player");
	player4->Active(true);
	player4->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
	player4->AddComponent(new PositionComponent(SDL_Point{ 200, 380 }));
	player4->AddComponent(new AttributesComponent(20, 20, 4, 10, 100, 100));
	player4->AddComponent(new MovementComponent());
	player4->AddComponent(new WeaponComponent(WeaponType::RANGE));
	player4->AddComponent(new CollisionComponent(200, 380, 16, 16, 2));
	//player4->AddComponent(new AiLogicComponent()); //add this if AI is to control that player4
	//player4->AddComponent(new SeekComponent()); //and this if AI is to control that player4
	player4->AddComponent(new CurrencyComponent());
	player4->AddComponent(new SoundComponent("Scream", "play", false, 1, 30, 50));
	player4->AddComponent(new MusicComponent("Test", "play", true, 0, 100));
	player4->AddComponent(new NetworkIDComponent(3));
	player4->Transient(true);

	systemManager.healthSystem->AddEntity(player4, "???");
	for (int i = 0; i < 12; i++)
	{
		Entity* heart = new Entity("Heart");
		heart->Transient(true);
		heart->AddComponent(new PositionComponent());
		heart->AddComponent(new SpriteComponent("Hearts", 5, 0, 0, 0, 4, 4, 0));
		static_cast<SpriteComponent*>(heart->GetComponents()->back())->Relative(true);
		systemManager.healthSystem->AddEntity(heart, "PH4");
		systemManager.renderSystem->AddEntity(heart);
	}
	for (int i = 0; i < 6; i++)
	{
		Entity* heart = new Entity("Heart");
		heart->Transient(true);
		heart->AddComponent(new PositionComponent());
		heart->AddComponent(new SpriteComponent("Armors", 5, 0, 0, 0, 4, 4, 0));
		static_cast<SpriteComponent*>(heart->GetComponents()->back())->Relative(true);
		systemManager.healthSystem->AddEntity(heart, "PH4");
		systemManager.renderSystem->AddEntity(heart);
	}

	systemManager.movementSystem->AddEntity(player4);
	systemManager.renderSystem->AddEntity(player4);
	systemManager.collisionSystem->AddEntity(player4);
	systemManager.attackSystem->AddEntity(player4);
	systemManager.networkSystem->AddEntity(player4);
	systemManager.mementoSystem->AddEntity(player4);

	systemManager.movementSystem->AddEntity(player3);
	systemManager.renderSystem->AddEntity(player3);
	systemManager.collisionSystem->AddEntity(player3);
	systemManager.attackSystem->AddEntity(player3);
	systemManager.networkSystem->AddEntity(player3);
	systemManager.mementoSystem->AddEntity(player3);

	systemManager.movementSystem->AddEntity(player2);
	systemManager.renderSystem->AddEntity(player2);
	systemManager.collisionSystem->AddEntity(player2);
	systemManager.attackSystem->AddEntity(player2);
	systemManager.networkSystem->AddEntity(player2);
	systemManager.mementoSystem->AddEntity(player2);

	systemManager.movementSystem->AddEntity(player);
	systemManager.renderSystem->AddEntity(player);
	systemManager.collisionSystem->AddEntity(player);
	systemManager.attackSystem->AddEntity(player);
	systemManager.networkSystem->AddEntity(player);
	systemManager.mementoSystem->AddEntity(player);

	std::vector<Entity*> playerEntities;
	playerEntities.push_back(player4);
	playerEntities.push_back(player3);
	playerEntities.push_back(player2);
	playerEntities.push_back(player);

	systemManager.soundSystem->AddEntity(player); //local client player only?

	AchievementHandler *achievements = new AchievementHandler(&systemManager);

	InstanceManager instanceManager(&systemManager, &state, resourceManager, listener, aStar, playerEntities);

	while (state.ExitGame == false)
	{
		//Calculate and correct fps
		int avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		//Set text to be rendered
		if (avgFPS > 1)
		{
			//			cout << "FPS (With Cap) " << avgFPS << endl;;
		}
		//update ren
		++countedFrames;

		//If frame finished early
		int frameTicks = capTimer.getTicks();

		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);

			currentTime = SDL_GetTicks();
			if (currentTime > lastTime)
			{
				deltaTime = ((float)(currentTime - lastTime)) / 1000;

				input->handleInput();
				achievements->HandleAchievements();

				lastTime = currentTime;
			}

			SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
			SDL_RenderClear(gameRenderer);

			instanceManager.Update(deltaTime);
			systemManager.Update(deltaTime, playerEntities);

			SDL_RenderPresent(gameRenderer);
		}
	}

	SDL_RenderPresent(gameRenderer);

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	IMG_Quit();
	SDL_Quit();

	return 0;
}