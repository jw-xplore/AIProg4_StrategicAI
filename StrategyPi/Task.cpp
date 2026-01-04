#include "Task.h"

/*
Task::Task(std::initializer_list<Subtask> subtasks)
{
	//assignee = nullptr;
	currentSubTask = 0;
	finished = false;
	this->subtasks = subtasks;
}
*/

Task::Task(std::initializer_list<SubTaskFn> subtasks)
{
	currentSubTask = 0;
	finished = false;
	this->subtaskFns = subtasks;
}

Task::~Task()
{
	subtasks.clear();
}

void Task::Update(float dTime)
{
	/*
	if (currentSubTask >= subtasks.size())
		return;

	// Run and progress subtask
	bool running = subtasks[currentSubTask].Execute(dTime);

	if (!running)
		currentSubTask++;
		*/

	if (currentSubTask >= subtaskFns.size())
		return;

	// Run and progress subtask
	bool running = subtaskFns[currentSubTask](*assignee);

	if (!running)
		currentSubTask++;
}