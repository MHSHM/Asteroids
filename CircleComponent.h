#pragma once
#include "Component.h"
#include "Math.h"
class CircleComponent : public Component
{
public:
	CircleComponent(class Actor *owner);

	Vector2& GetCenter(); 

	void SetRadius(float radius) { mRadius = radius;  }

	float GetRadius() { return mRadius;  };

private:
	float mRadius; 

};


bool Intersect(CircleComponent &c1, CircleComponent &c2);
