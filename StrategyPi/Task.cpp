#include "Task.h"

Task::Task(std::initializer_list<SubTaskFn> subtasks)
{
	currentSubTask = 0;
	finished = false;
	this->subtaskFns = subtasks;
}

Task::~Task()
{
	subtaskFns.clear();
}

void Task::Update(float dTime)
{
	if (currentSubTask >= subtaskFns.size())
		return;

	// Run and progress subtask
	bool running = subtaskFns[currentSubTask](*assignee, dTime);

	if (!running)
		currentSubTask++;
}