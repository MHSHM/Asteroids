#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor *owner);
	virtual ~InputComponent();

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxForwardSpeed() { return mMaxForwardSpeed;  }
	float GetMinForwardSpeed() { return mMaxAngularSpeed;  }
	int GetForwardKey() { return mForwardKey;  }
	int GetBackwardKey() { return mBackwardKey;  }
	int GetClockwiseKey() { return mClocwiseKey;  }
	int GetAnticlockwiseKey() { return mAntiClockwiseKey;  }

	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackwardKey = key; }
	void SetClockwiseKey(int key) { mClocwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mAntiClockwiseKey = key; }
	void SetForwardForce(Vector2 force) { mForwardForce = force; }
	void SetBackwardForce(Vector2 force) { mBackwardForce = force;  }


private:
	float mMaxForwardSpeed; 
	float mMaxAngularSpeed; 

	int mForwardKey; 
	int mBackwardKey;

	int mClocwiseKey; 
	int mAntiClockwiseKey; 

	Vector2 mForwardForce; 
	Vector2 mBackwardForce; 
};

