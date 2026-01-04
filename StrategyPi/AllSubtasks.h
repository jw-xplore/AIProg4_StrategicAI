#pragma once
#include "Task.h"

class World;
class Worker;

enum EMaterialResourceType;

class FindClosestResourceSubtaks : public Subtask
{
public:
	World* world; Worker* worker;  EMaterialResourceType type;

	void AssignResources(World* world, Worker* worker, EMaterialResourceType type)
	{
		this->world = world;
		this->worker = worker;
		this->type = type;
	}

	bool Execute(float dTime) override;
};

