#pragma once
#include "Component.h"
#include <SDL.h>
#include <SDL_image.h>

class SpriteComponent :public Component
{
public:
	SpriteComponent(class Actor *owner , int drawOrder = 100);
	virtual ~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer); 
	virtual void SetTexture(SDL_Texture* texture); 

	int GetDrawOrder() { return mDrawOrder;  }
	int GetTextureWidth() { return mTextureWidth;  }
	int GetTextureHeight() { return mTextureHeight;  }

private:
	int mDrawOrder; 

	SDL_Texture *mTexture; 

	int mTextureWidth; 
	int mTextureHeight; 
};

