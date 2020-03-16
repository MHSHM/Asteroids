#include "pch.h"
#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Asteroid.h"
#include "Ship.h" 
#include "Random.h"


Game::Game() :
	mWindow(nullptr),
	mRenderer(nullptr),
	mIsRunning(true),
	mIsUpdating(false)
{

}

bool Game::Initialize() 
{
	int init = SDL_Init(SDL_INIT_VIDEO); 
	if (init != 0) 
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Asteroids", 100, 100, 1024, 768, 0); 
	if (mWindow == nullptr) 
	{
		SDL_Log("Unable to create window SDL: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
	if (mRenderer == nullptr) 
	{
		SDL_Log("Unable to create window SDL: %s", SDL_GetError());
		return false;
	}

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted&flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
	}

	Random::Init();
	mTicksCount = SDL_GetTicks(); 
	LoadData(); 
	return true; 
}

void Game::LoadData() 
{
	mShip = new Ship(this); 

	const int asteroids = 10; 

	for (int i = 0; i < asteroids; ++i) 
	{
		new Asteroid(this); 
	}
}

void Game::ProcessInput() 
{
	SDL_Event event; 

	while (SDL_PollEvent(&event)) 
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false; 
				break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL); 
	if (keyState[SDL_SCANCODE_ESCAPE]) 
	{
		mIsRunning = false; 
	}
	
	mIsUpdating = true; 
	for (auto actor : mActors) 
	{
		actor->ProcessInput(keyState); 
	}
	mIsUpdating = false; 
}

void Game::UpdateGame() 
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f; 
	
	if (deltaTime > 0.05f) 
	{
		deltaTime = 0.05f; 
	}

	mTicksCount = SDL_GetTicks(); 

	mIsUpdating = true; 
	for (auto actor : mActors) 
	{
		actor->Update(deltaTime); 
	}
	mIsUpdating = false; 

	for (auto pending : mPendingActors) 
	{
		mActors.emplace_back(pending); 
	}
	mPendingActors.clear(); 

	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor; 
	}

}

void Game::GenerateOutput() 
{
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer); 


	for (auto sprite : mSprites) 
	{
		if (sprite->GetOwner()->GetState() == sprite->GetOwner()->IsActive()) 
		{
			sprite->Draw(mRenderer); 
		}
	}

	SDL_RenderPresent(mRenderer); 
}

SDL_Texture* Game::GetTexture(std::string filename)
{
	SDL_Texture *texture = nullptr; 

	auto it = mTextures.find(filename); 

	if (it != mTextures.end()) 
	{
		texture = it->second;
	}
	else 
	{
		SDL_Surface *surface = IMG_Load(filename.c_str()); 
		if (!surface) 
		{
			SDL_Log("Failed to load texture file %s", filename.c_str());
			return nullptr;
		}

		texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);
		if (!texture) 
		{
			SDL_Log("Failed to load texture file %s", filename.c_str());
			return nullptr;
		}
		mTextures.emplace(filename.c_str(), texture); 
	}
	return texture; 
}

void Game::AddSprite(SpriteComponent *spriteComponent) 
{
	int order = spriteComponent->GetDrawOrder(); 
	auto it = mSprites.begin(); 

	for (; it != mSprites.end(); ++it) 
	{
		if (order < (*it)->GetDrawOrder()) 
		{
			break; 
		}
	}

	mSprites.insert(it, spriteComponent); 
}

void Game::RemoveSprite(SpriteComponent *spriteComponent) 
{
	auto it = std::find(mSprites.begin(), mSprites.end(), spriteComponent); 
	if (it != mSprites.end()) 
	{
		mSprites.erase(it); 
	}
}

void Game::AddActor(Actor *actor) 
{
	if (mIsUpdating) 
	{
		mPendingActors.emplace_back(actor); 
	}
	else 
	{
		mActors.emplace_back(actor); 
	}
}

void Game::RemoveActor(Actor *actor) 
{
	auto it1 = std::find(mPendingActors.begin(), mPendingActors.end(), actor); 

	if (it1 != mPendingActors.end()) 
	{
		std::iter_swap(it1, mPendingActors.end() - 1); 
		mPendingActors.pop_back(); 
	}

	auto it2 = std::find(mActors.begin(), mActors.end(), actor); 
	if (it2 != mActors.end()) 
	{
		std::iter_swap(it2, mActors.end() - 1); 
		mActors.pop_back(); 
	}
}

void Game::AddAsteroid(Asteroid *ast) 
{
	mAsteroids.emplace_back(ast); 
}

void Game::RemoveAsteroid(Asteroid *ast) 
{
	auto it = std::find(mAsteroids.begin(), mAsteroids.end(), ast); 
	if (it != mAsteroids.end()) 
	{
		mAsteroids.erase(it); 
	}
}

void Game::RunGame() 
{
	while (mIsRunning) 
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::UnloadData() 
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}



void Game::Shutdown() 
{
	UnloadData(); 
	IMG_Quit(); 
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow); 
	SDL_Quit(); 
}


Game::~Game()
{
}
