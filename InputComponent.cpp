#include "pch.h"
#include "InputComponent.h"
#include "Actor.h"


InputComponent::InputComponent(Actor *owner):
	MoveComponent(owner)
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.0f;  
	if (keyState[mForwardKey]) 
	{
		forwardSpeed += mMaxForwardSpeed; 
	}
	if (keyState[mBackwardKey]) 
	{
		forwardSpeed -= mMaxForwardSpeed; 
	}
	SetForwardSpeed(forwardSpeed); 

	float angularSpeed = 0.0f; 
	if (keyState[mClocwiseKey]) 
	{
		angularSpeed += mMaxAngularSpeed; 
	}
	if (keyState[mAntiClockwiseKey]) 
	{
		angularSpeed -= mMaxAngularSpeed; 
	}
	SetAngularSpeed(angularSpeed); 
}

InputComponent::~InputComponent()
{
}
