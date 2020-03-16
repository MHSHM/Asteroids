#include "pch.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"


SpriteComponent::SpriteComponent(Actor *owner, int drawOrder):
	Component(owner),
	mTexture(nullptr),
	mTextureWidth(0),
	mTextureHeight(0),
	mDrawOrder(drawOrder)
{
	owner->GetGame()->AddSprite(this); 
}


void SpriteComponent::Draw(SDL_Renderer *renderer) 
{
	if (mTexture) 
	{
		SDL_Rect r; 

		r.w = static_cast<int>(owner->GetScale() * mTextureWidth); 
		r.h = static_cast<int>(owner->GetScale() * mTextureHeight); 

		r.x = static_cast<int>(owner->GetPos().x - r.w / 2); 
		r.y = static_cast<int>(owner->GetPos().y - r.h / 2);

		SDL_RenderCopyEx(renderer, mTexture, NULL, &r, -Math::ToDegrees(owner->GetRotation()), NULL, SDL_FLIP_NONE);	
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture) 
{
	mTexture = texture; 
	SDL_QueryTexture(texture, NULL, NULL, &mTextureWidth, &mTextureHeight); 
}

SpriteComponent::~SpriteComponent()
{
	owner->GetGame()->RemoveSprite(this); 
}
