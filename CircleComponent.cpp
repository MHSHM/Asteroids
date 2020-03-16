#include "pch.h"
#include "CircleComponent.h"
#include "Actor.h"


CircleComponent::CircleComponent(Actor *owner):
	Component(owner),
	mRadius(0.0f)
{
}

Vector2& CircleComponent::GetCenter() 
{
	return owner->GetPos(); 
}

bool Intersect(CircleComponent &c1, CircleComponent &c2) 
{
	Vector2 v = c1.GetCenter() - c2.GetCenter();
	float dist = v.LengthSq(); 
	float radiusSum = c1.GetRadius() + c2.GetRadius(); 
	radiusSum *= radiusSum; 
	return dist <= radiusSum; 
}
