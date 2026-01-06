#include "Commander.h"
#include "EntityManager.h"
#include "Task.h"
#include "Worker.h"
#include "SubtaskDefinitions.h"
#include "World.h"

//Commander data storage
struct Commander::Data
{
	// Task types
	/*
	Task gatherWoodBlueprint = Task({
		FindClosestResourceSubtaks()
		});

	*/

	Task gatherWoodBlueprint = Task({
		[](Worker& worker) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::Coal);  },
		[](Worker& worker) { return SubtaskDefinitions::Arrive(worker); }
		});

	//Data();
};

// Commander
Commander::Commander(EntityManager* entityManager)
{
	data = new Commander::Data{};
	this->entityManager = entityManager;
	
	// Test command
	//Task testTask = data->gatherWoodTask;

	/*
	Task testTask = data->gatherWoodBlueprint;
	testTask.assignee = this->entityManager->workers[0];

	activeTasks.push_back(testTask);
	*/
}

Commander::~Commander()
{
	activeTasks.clear();
	delete data;
}

void Commander::Update(float dTime)
{
	for (size_t i = 0; i < activeTasks.size(); i++)
	{
		activeTasks[i].Update(dTime);
	}
}