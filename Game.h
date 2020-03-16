#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>



class Game
{
public:
	Game();
	~Game();

	bool Initialize(); 
	void RunGame(); 
	void Shutdown(); 

	void AddActor(class Actor *actor); 
	void RemoveActor(class Actor *actor); 

	void AddSprite(class SpriteComponent *spriteComponent); 
	void RemoveSprite(class SpriteComponent *spriteComponent); 

	void AddAsteroid(class Asteroid* ast); 
	void RemoveAsteroid(class Asteroid* ast); 


	SDL_Texture* GetTexture(std::string filename);
	SDL_Renderer *GetRenderer() { return mRenderer;  }

	class Ship *GetShip() { return mShip;  }

	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }

private:
	void ProcessInput(); 
	void UpdateGame(); 
	void GenerateOutput(); 
	void LoadData(); 
	void UnloadData(); 

	std::vector<class Actor*> mActors;
	std::vector<class Actor* > mPendingActors;
	std::vector<class SpriteComponent*> mSprites; 
	std::vector<class Asteroid*> mAsteroids; 

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	SDL_Window *mWindow; 
	SDL_Renderer *mRenderer; 

	Uint32 mTicksCount; 

	bool mIsRunning; 
	bool mIsUpdating;

	class Ship *mShip; 
};

