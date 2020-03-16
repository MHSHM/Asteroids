#include "pch.h"
#include "Actor.h"
#include "Game.h"
#include <algorithm>
#include "Component.h"
#include "Math.h"

Actor::Actor(Game *game):
	mState(EActive),
	mPos(Vector2::Zero),
	mScale(1.0f),
	mRotation(0.0f),
	game(game)

{
	game->AddActor(this); 
}


void Actor::AddComponent(Component *component) 
{
	int order = component->GetUpdateOrder(); 

	auto it = mComponents.begin(); 

	for (; it != mComponents.end(); ++it) 
	{
		if (order < (*it)->GetUpdateOrder()) 
		{
			break; 
		}
	}

	mComponents.insert(it, component); 
}

void Actor::RemoveComponent(Component *component) 
{
	auto it = std::find(mComponents.begin(), mComponents.end(), component);

	if (it != mComponents.end()) 
	{
		mComponents.erase(it); 
	}
}

void Actor::ProcessInput(const uint8_t* keyState) 
{
	if (mState == EActive) 
	{
		for (auto comp : mComponents) 
		{
			comp->ProcessInput(keyState); 
		}
	}
	if (mState == EActive) { ActorInput(keyState); }
}

void Actor::ActorInput(const uint8_t* keyState) 
{

}

void Actor::Update(float deltaTime) 
{
	if (mState == EActive || mState == EPaused) 
	{ 
		UpdateActor(deltaTime);
		if (mState == EActive) { UpdateComponents(deltaTime) ; }
	}
}

void Actor::UpdateComponents(float deltaTime) 
{
	for (auto comp : mComponents) 
	{
		comp->Update(deltaTime); 
	}
}

void Actor::UpdateActor(float deltaTime) 
{

}


Actor::~Actor()
{
	game->RemoveActor(this); 
	//delete actor components
	while (!mComponents.empty()) 
	{
		delete mComponents.back(); 
	}
}
