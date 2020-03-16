#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor *owner , int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime); 
	virtual void ProcessInput(const uint8_t* keyState) {};

	class Actor *GetOwner() { return owner;  }
	int GetUpdateOrder() { return mOrder;  }

protected:
	int mOrder; 
	class Actor *owner; 
};

