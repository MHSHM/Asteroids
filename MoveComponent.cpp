#include "pch.h"
#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"


MoveComponent::MoveComponent(Actor *owner, int updateOrder) :
	Component(owner, updateOrder),
	mAngularSpeed(0.0f),
	mForwardSpeed(0.0f)
{
}

void MoveComponent::Update(float deltaTime) 
{
	if (!Math::NearZero(mAngularSpeed)) 
	{
		float rot = owner->GetRotation(); 
		rot += mAngularSpeed; 
		owner->SetRotation(rot); 
	}


	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = owner->GetPos(); 
		pos += mForwardSpeed * owner->GetForward() * deltaTime;
		if (pos.x < 0.0f) { pos.x = 1022.0f;  }
		else if (pos.x > 1024.0f) { pos.x = 2.0f;  }

		if (pos.y < 0.0f) { pos.y = 766.0f;  }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }
		owner->SetPos(pos); 
	}
}


MoveComponent::~MoveComponent()
{
}
