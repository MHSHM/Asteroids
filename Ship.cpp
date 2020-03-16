#include "pch.h"
#include "Ship.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Lase.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Ship::Ship(Game *game) :
	Actor(game),
	coolDown(0.0f),
	delay(2.5f),
	respawnTime(3.0f)
{
	Vector2 pos;
	pos.x = 1024.0f / 2.0f; 
	pos.y = 768.0f / 2.0f; 
	SetPos(pos); 
	SetRotation(Math::PiOver2);

	SpriteComponent *shipSprite = new SpriteComponent(this); 
	SDL_Texture *texture =  game->GetTexture("Assets/ShipWithThrust.png");
	shipSprite->SetTexture(texture); 

	InputComponent *shipInput = new InputComponent(this); 
	
	shipInput->SetForwardKey(SDL_SCANCODE_W); 
	shipInput->SetBackKey(SDL_SCANCODE_S); 
	shipInput->SetClockwiseKey(SDL_SCANCODE_A); 
	shipInput->SetCounterClockwiseKey(SDL_SCANCODE_D); 
	shipInput->SetMaxForwardSpeed(350.0f); 
	shipInput->SetMaxAngularSpeed(0.05f); 
	
	mCircle = new CircleComponent(this); 
	mCircle->SetRadius(40.0f); 
}

void Ship::UpdateActor(float deltaTime) 
{
	if (coolDown > 0.0f) { coolDown -= deltaTime; }
	if (delay > 0.0f) { delay -= deltaTime; }

	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())) && delay <= 0.0f && GetState() == EActive)
		{
			SetState(EPaused); 
		}
	}

	if (GetState() == EPaused) { respawnTime -= deltaTime; }

	if (respawnTime <= 0.0f) 
	{
		SetState(EActive); 
		SetPos(Vector2(1024 / 2, 768 / 2)); 
		SetRotation(Math::PiOver2);
		respawnTime = 3.0f; 
		delay = 2.5f; 
	}
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && coolDown <= 0.0f) 
	{
		Lase *laser = new Lase(GetGame());
		laser->SetPos(GetPos()); 
		laser->SetRotation(GetRotation()); 
		coolDown = 0.5f; 
	}
}
