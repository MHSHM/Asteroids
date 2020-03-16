#include "pch.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Asteroid.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Random.h"


Asteroid::Asteroid(Game *game):
	Actor(game)
{
	Vector2 pos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f)); 
	SetPos(pos); 
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent *astSprite = new SpriteComponent(this); 
	SDL_Texture *texture = game->GetTexture("Assets/Rock.png"); 
	astSprite->SetTexture(texture); 

	MoveComponent *astMove = new MoveComponent(this);  
	astMove->SetForwardSpeed(250.0f);

	mCircle = new CircleComponent(this); 
	mCircle->SetRadius(40.0f);

	game->AddAsteroid(this); 
}


Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this); 
}
