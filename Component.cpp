#include "pch.h"
#include "Component.h"
#include "Actor.h"


Component::Component(Actor *actor , int updateOrder):
	owner(actor),
	mOrder(updateOrder)
{
	owner->AddComponent(this); 
}


void Component::Update(float deltaTime)
{

}

Component::~Component()
{
	owner->RemoveComponent(this); 
}

