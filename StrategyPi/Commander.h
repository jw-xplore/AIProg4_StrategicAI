#pragma once
#include <vector>

class EntityManager;
class Worker;

class Task;
class Subtask;

/*
Assigns tasks to NPCs and manages their resources like path
*/
class Commander
{
public:
	// Data storage
	struct Data;
	Data* data;

	EntityManager* entityManager;

	std::vector<Task> activeTasks;

	Commander(EntityManager* entityManager);

	void Update(float dTime);
};

