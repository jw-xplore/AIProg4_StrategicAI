#pragma once
#include <vector>
#include <functional>

//Small event that actually makes character for do things
class Subtask
{
public:
	virtual bool Execute(float dTime) { return true; } // Task is considered done if returns false
};

class Worker;

using SubTaskFn = std::function<bool(Worker&)>;

// Holds several subtasks and manage their step by step execution
class Task
{
public:
	bool finished;
	int currentSubTask = 0;
	std::vector<Subtask> subtasks;

	std::vector<SubTaskFn> subtaskFns;

	Worker* assignee;

	//Task(std::initializer_list<Subtask> subtasks);
	Task(std::initializer_list<SubTaskFn> subtasks);
	~Task();

	void Update(float dTime);
};

