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

	// Resources
	int wood = 0;
	int coal = 0;
	int iron = 0;
	int swords = 0;
	int soldiers = 0;

	EntityManager* entityManager;

	std::vector<Task> activeTasks;

	Commander(EntityManager* entityManager);
	~Commander();

	void Update(float dTime);
	void DrawUI();
};

