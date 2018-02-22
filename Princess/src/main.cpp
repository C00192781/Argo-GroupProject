#define SDL_MAIN_HANDLED

#include "InstanceManager.h"
#include "SystemManager.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "LTimer.h"
#include "AchievementHandler.h"
#include <chrono>
#include <time.h>
#include "Client.h"

int main()
{
	SDL_Window* gameWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 816, 624, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

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

	const int SCREEN_FPS = 500;
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

	ResourceManager *resourceManager = new ResourceManager(gameRenderer, "Resources");

	resourceManager->AddTexture("Red", "Sprite_Red.png");
	resourceManager->AddTexture("Demon", "demon.png");
	resourceManager->AddTexture("Turf", "Turfs.png");
	resourceManager->AddTexture("Arrow", "Arrow.png");
	resourceManager->AddTexture("HeartsSheet", "heartSpriteSheet.png");
	resourceManager->AddTexture("ArmourSheet", "armourSpriteSheet.png");
	resourceManager->AddTexture("WorldTurf", "World_Turfs.png");
	resourceManager->AddTexture("Button", "Button.png");
	resourceManager->AddTexture("Achievement", "PlaceholderAchievement.png");
	resourceManager->AddTexture("Achievement2", "PlaceholderAchievement2.png");
	
	resourceManager->AddMusic("Test", "kevin.mp3");
	resourceManager->AddSound("Scream", "test.wav");
	resourceManager->AddSound("Placeholder", "placeholder.wav");
	
	resourceManager->AddFont("ComicSans", "ComicSans.ttf", 32);

	Mix_AllocateChannels(6);

	EventListener *listener = new EventListener();

	InputHandler *input = new InputHandler(listener, e);

	StateManager state;

	std::vector<Entity*>* projectiles = new std::vector<Entity*>;

	SystemManager systemManager(resourceManager, gameRenderer, listener, projectiles);

	InstanceManager instanceManager(&systemManager, &state, resourceManager, listener);

	Client client;
	if (client.connectToServer())
	{
		std::cout << "AYY" << std::endl;
	}

	Entity * player = new Entity("Player");
	player->Active(true);
	player->AddComponent(new SpriteComponent("Red", 2, 1, 0, 0, 16, 16, 0));
	player->AddComponent(new PositionComponent(SDL_Point{ 500, 380 }));
	player->AddComponent(new AttributesComponent(26, 26, 10, 10, 200, 200));
	player->AddComponent(new MovementComponent());
	player->AddComponent(new WeaponComponent(WeaponType::RANGE));
	player->AddComponent(new CollisionComponent(100, 300, 16, 16, 2));
	player->AddComponent(new SoundComponent("Scream", "play", false, 1, 30, 50));
	//player->AddComponent(new SoundComponent("Placeholder", "play", true, 0, 0, 80));
	player->AddComponent(new MusicComponent("Test", "play", true, 0, 100));
	player->Transient(true);

	systemManager.controlSystem->AddEntity(player);
	systemManager.movementSystem->AddEntity(player);
	systemManager.renderSystem->AddEntity(player);
	systemManager.collisionSystem->AddEntity(player);
	systemManager.attackSystem->AddEntity(player);
	systemManager.soundSystem->AddEntity(player);

	AchievementHandler *achievements = new AchievementHandler(&systemManager);

	bool heartTest = true;

	while (true)
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
			//cout << "FPS (With Cap) " << avgFPS << endl;;
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
			systemManager.Update(deltaTime);
			client.listen();

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
