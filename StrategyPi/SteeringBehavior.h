#pragma once

#include "vector"
#include "Entity.h"
#include <raymath.h>

struct SteerTarget
{
public:
	Vector2 position = { 0,0 };
	Vector2 prevPosition = { 0,0 };
	Vector2 velocity = { 0,0 };
};

class SteeringBehaviorData
{
public:
	std::vector<Entity*> separationObstacles;

	SteeringBehaviorData() {}
	~SteeringBehaviorData()
	{
		separationObstacles.clear();
	}
};

namespace SteeringBehavior
{
	inline Vector2 seek(SteerTarget* target, Vector2 pos, float maxAccel)
	{
		Vector2 acceleration = target->position - pos;
		acceleration = Vector2Normalize(acceleration);

		return acceleration * maxAccel;
	}

	inline Vector2 flee(SteerTarget* target, Vector2 pos, float maxAccel)
	{
		Vector2 acceleration = pos - target->position;
		acceleration = Vector2Normalize(acceleration);

		return acceleration * maxAccel;
	}

	inline Vector2 arrive(SteerTarget* target, Vector2 pos, Vector2 vel, float maxVel, float maxAccel, float radius, float timeToTarget)
	{
		Vector2 direction = target->position - pos;
		float distance = Vector2Length(direction);

		// Stop
		if (distance < radius)
		{
			return Vector2{ 0, 0 };
		}

		// Adjust velocity
		float slowRadius = 100;
		float targetSpeed;

		if (distance > slowRadius)
		{
			targetSpeed = maxVel;
		}
		else
		{
			targetSpeed = maxVel * distance / slowRadius;
		}

		Vector2 targetVelocity = direction;
		targetVelocity = Vector2Normalize(targetVelocity);
		targetVelocity *= targetSpeed;

		// Adjust acceleration
		Vector2 acceleration = targetVelocity - vel;
		acceleration /= timeToTarget;

		if (Vector2Length(acceleration) > maxAccel)
		{
			acceleration = Vector2Normalize(acceleration);
			acceleration = acceleration * maxAccel;
		}

		return acceleration;
	}

	inline Vector2 separate(std::vector<Entity*> obstacles, Entity* self, Vector2 pos, float threshold, float maxAccel)
	{
		Vector2 acceleration = { 0,0 };
		Vector2 dir;
		float dist;

		for (int i = 0; i < obstacles.size(); i++)
		{
			if (obstacles[i] == self)
				continue;

			dir = obstacles[i]->position - pos;
			dist = Vector2Length(dir);

			if (dist < threshold)
			{
				float strenght = maxAccel * (threshold - dist) / threshold;
				dir = Vector2Normalize(dir);
				acceleration = { -dir.x * strenght, -dir.y * strenght };
			}
		}

		return acceleration;
	}
};