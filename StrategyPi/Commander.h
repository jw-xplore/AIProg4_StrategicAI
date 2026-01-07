#pragma once
#include <vector>

class EntityManager;
class Worker;

class Task;
class Subtask;
class ComponentsManager;

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

	Commander(ComponentsManager* componentManager, EntityManager* entityManager);
	~Commander();

	void Update(float dTime);
	void DrawUI();
};

