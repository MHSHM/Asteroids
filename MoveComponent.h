#pragma once
#include "Component.h"
#include <vector>
#include "Math.h"
class MoveComponent : public Component
{
public:
	MoveComponent(class Actor *owner , int updateOrder = 10);
	~MoveComponent();

	void Update(float deltaTime) override; 

	void SetForwardSpeed(float val) { mForwardSpeed = val; }
	void SetAngularSpeed(float val) { mAngularSpeed = val;  }

	float GetForwardSpeed() { return mForwardSpeed;  }
	float GetAngularSpeed() { return mAngularSpeed;  }


private:
	float mForwardSpeed; 
	float mAngularSpeed; 
};

