#pragma once
#include <vector>

//Small event that actually makes character for do things
class Subtask;

// Holds several subtasks and manage their step by step execution
class Task
{
public:
	bool finished;
	int currentSubTask = 0;
	int subtaskCount = 0;
	Subtask* subtasks;

	Task(std::initializer_list<Subtask> subtasks);
	~Task();
};

