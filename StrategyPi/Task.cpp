#include "Task.h"

Task::Task(std::initializer_list<SubTaskFn> subtasks)
{
	currentSubTask = 0;
	//finished = false;
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
	ESubtaskState state = subtaskFns[currentSubTask](*assignee, dTime);

	if (state == ESubtaskState::Canceled)
	{
		// End task execution
		currentSubTask = subtaskFns.size();
		return;
	}

	if (state == ESubtaskState::Finnished || state == ESubtaskState::Skipped)
		currentSubTask++;
}