/*
Custom Entity class from previous DOD course Snake project.
Handles basic game object functionality like update, drawing, translation.
Entity is supposed to be use in combination with EntityManager to handle creation, update, management (ids) and deletion.
*/

#pragma once
#include <raylib.h>

struct SteeringOutput
{
	Vector2 linear;
	float angular;
};

class Entity
{
private:
	int id = -1;

public:
	Vector2 position = { 0,0 };
	Vector2 velocity = { 0,0 };
	Vector2 pivotPoint = { 0,0 };
	float orientation = 0;
	float rotation = 0;

	SteeringOutput* steering;

	Entity();
	virtual ~Entity();
	void Destroy();
	virtual void Update(float dTime);
	virtual void Draw() {}

	bool SetId(int id);
	int GetId();

	Vector2 GetPosition();
	void SetPosition(Vector2 position);
	void SetPosition(float x, float y);
	void Translate(Vector2 position);
	void Translate(float x, float y);
	Vector2 GetVelocity();
	void SetVelocity(Vector2 velocity);
};