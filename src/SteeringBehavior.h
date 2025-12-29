#pragma once

#include "vector"
#include "Entity.h"

struct SteerTarget
{
public:
	Vector2 position = { 0,0 };
	Vector2 prevPosition = { 0,0 };
	Vector2 velocity = { 0,0 };
};

class SteeringBehavior
{
public:
	std::vector<Entity*> separationObstacles;

	Vector2 seek(SteerTarget* target, Vector2 pos, float maxAccel);
	Vector2 flee(SteerTarget* target, Vector2 pos, float maxAccel);
	Vector2 arrive(SteerTarget* target, Vector2 pos, Vector2 vel, float maxVel, float maxAccel, float radius, float timeToTarget);
	Vector2 separate(std::vector<Entity*> obstacles, Entity* self, Vector2 pos, float threshold, float maxAccel);
};