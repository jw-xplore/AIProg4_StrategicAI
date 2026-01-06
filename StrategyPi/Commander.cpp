#include "Commander.h"
#include "EntityManager.h"
#include "Task.h"
#include "Worker.h"
#include "SubtaskDefinitions.h"
#include "World.h"
#include "Constants.h"
#include <string>

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
		[](Worker& worker) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker) { return SubtaskDefinitions::MineAtPosition(worker); }
		});

	//Data();
};

// Commander
Commander::Commander(EntityManager* entityManager)
{
	data = new Commander::Data{};
	this->entityManager = entityManager;
	

	wood = 0;
	coal = 0;
	iron = 0;
	swords = 0;
	soldiers = 0;

	// Test command
	Task testTask = data->gatherWoodBlueprint;
	testTask.assignee = this->entityManager->workers[0];

	Task testTask2 = data->gatherWoodBlueprint;
	testTask2.assignee = this->entityManager->workers[1];

	activeTasks.push_back(testTask);
	//activeTasks.push_back(testTask2);
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

void Commander::DrawUI()
{
	DrawRectangle(0, GlobalVars::SCREEN_HEIGHT - 100, GlobalVars::SCREEN_WIDTH, 100, GRAY);

	int yPos = GlobalVars::SCREEN_HEIGHT - 50;

	std::string strWood = "Wood: " + std::to_string(wood);
	char const* txtWood = strWood.c_str();
	DrawText(txtWood, 50, yPos, 24, BLACK);

	std::string strCoal = "Coal: " + std::to_string(coal);
	char const* txtCoal = strCoal.c_str();
	DrawText(txtCoal, 180, yPos, 24, BLACK);

	std::string strIron = "Iron: " + std::to_string(iron);
	char const* txtIron = strIron.c_str();
	DrawText(txtIron, 300, yPos, 24, BLACK);

	std::string strSwords = "Swords: " + std::to_string(swords);
	char const* txtSwords = strSwords.c_str();
	DrawText(txtSwords, 450, yPos, 24, BLACK);

	std::string stSoldiers = "Soldiers: " + std::to_string(soldiers);
	char const* txtSoldiers = stSoldiers.c_str();
	DrawText(txtSoldiers, 600, yPos, 24, BLACK);
}