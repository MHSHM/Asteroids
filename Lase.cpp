#include "pch.h"
#include "Lase.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"



Lase::Lase(Game *game) :
	Actor(game),
	deathTimer(1.5f)
{

	SpriteComponent *laserSprite = new SpriteComponent(this); 
	SDL_Texture *texture = game->GetTexture("Assets/spaceMissiles_037.png"); 
	laserSprite->SetTexture(texture); 

	MoveComponent *laserMove = new MoveComponent(this); 
	laserMove->SetForwardSpeed(850.0f);

	mCircle = new CircleComponent(this); 
	mCircle->SetRadius(11.0f); 
}

void Lase::UpdateActor(float deltaTime) 
{
	deathTimer -= deltaTime; 
	if (deathTimer <= 0.0f) 
	{
		SetState(EDead); 
	}
	else 
	{
		for (auto ast : GetGame()->GetAsteroids()) 
		{
			if (Intersect(*mCircle , *(ast->GetCircle()))) 
			{
				SetState(EDead); 
				ast->SetState(EDead); 
				break; 
			}
		}
	}
}