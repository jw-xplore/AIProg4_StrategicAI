#include "Entity.h"
#include <raymath.h>

Entity::Entity()
{
	steering = new SteeringOutput();
}

Entity::~Entity()
{
	delete steering;
}

// Update basic entity behavior
// This base should be used when overriding method
void Entity::Update(float dTime)
{
	// Apply velocity on position change
	this->position += this->velocity * dTime;
	this->orientation += this->rotation * dTime;

	this->velocity += this->steering->linear * dTime;
	this->rotation += this->steering->angular * dTime;

	// Base behavior
	//Draw();
}

void Entity::Destroy()
{
	delete this;
}

// Set id if it has not been set (this->id == -1)
// Returns true only if id was not set and parameter id is positive
bool Entity::SetId(int id)
{
	if (this->id != -1 or id < 0)
		return false;

	this->id = id;
	return true;
}

int Entity::GetId()
{
	return id;
}

// Returns absoulute position in game world
Vector2 Entity::GetPosition()
{
	return position + pivotPoint;
}

// Set absolute position to point
void Entity::SetPosition(Vector2 position)
{
	this->position = position;
}

// Set absolute position to x, y coordinates
void Entity::SetPosition(float x, float y)
{
	this->position = { x, y };
}

// Move absolute position by point
void Entity::Translate(Vector2 position)
{
	this->position += position;
}

// Move absolute position by x, y coordinates
void Entity::Translate(float x, float y)
{
	this->position.x += x;
	this->position.y += y;
}

Vector2 Entity::GetVelocity()
{
	return velocity;
}

void Entity::SetVelocity(Vector2 velocity)
{
	this->velocity = velocity;
}