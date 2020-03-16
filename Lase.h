#pragma once
#include "Actor.h"
class Lase : public Actor
{
public:
	Lase(class Game* game);


	class CircleComponent *GetCircle() { return mCircle;  }

	void UpdateActor(float deltaTime) override;

private:
	float deathTimer; 

	class CircleComponent *mCircle; 
};

