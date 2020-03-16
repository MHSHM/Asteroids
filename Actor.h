#pragma once

#include <vector>
#include "Math.h"
#include <cstdint>

class Actor
{
public:
	Actor(class Game *game);
	virtual ~Actor();

	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	void AddComponent(class Component *component);
	void RemoveComponent(class Component *component);

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void SetPos(Vector2 position) { mPos = position; }
	void SetRotation(float val) { mRotation = val; }
	void SetScale(float val) { mScale = val; }
	void SetState(State val) { mState = val; }
	State IsActive() { return EActive; }
	State IsPaused() { return EPaused; }
	State IsDead() { return EDead; }

	Vector2& GetPos() { return mPos; }
	float GetRotation() { return mRotation; }
	float GetScale() { return mScale; }
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	State GetState()  { return mState; }
	class Game* GetGame() { return game;  }

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState); 

private:

	std::vector<class Component*> mComponents; 

	State mState; 

	Vector2 mPos; 
	float mRotation; 
	float mScale; 

	class Game *game; 
};

