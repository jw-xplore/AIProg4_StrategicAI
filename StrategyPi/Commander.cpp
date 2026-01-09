#include "Commander.h"
#include "EntityManager.h"
#include "Task.h"
#include "Worker.h"
#include "SubtaskDefinitions.h"
#include "World.h"
#include "Constants.h"
#include <string>
#include "GatheredResources.h"
#include "ComponentsManager.h"

//Commander data storage
struct Commander::Data
{
	// Task types

	// TODO: Define exploration task

	Task gatherWoodBlueprint = Task({
		[](Worker& worker, float dTime) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::Wood);  },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::MineAtPosition(worker, dTime); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::BuildingStorage);  },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::SubmitMaterial(worker, dTime); },
		});

	Task gatherCoalBlueprint = Task({
		[](Worker& worker, float dTime) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::Coal);  },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::MineAtPosition(worker, dTime); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::BuildingStorage);  },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::SubmitMaterial(worker, dTime); },
		});

	Task gatherIronBlueprint = Task({
		[](Worker& worker, float dTime) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::Iron);  },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::MineAtPosition(worker, dTime); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::BuildingStorage);  },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::SubmitMaterial(worker, dTime); },
		});

	Task buildSmithyBlueprint = Task({
		[](Worker& worker, float dTime) { return SubtaskDefinitions::PickBuildPosition(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::CreateBuilding(worker, dTime, EMaterialResourceType::BuildingSmithy); },
		});

	Task buildBarracksBlueprint = Task({
		[](Worker& worker, float dTime) { return SubtaskDefinitions::PickBuildPosition(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::CreateBuilding(worker, dTime, EMaterialResourceType::BuildingBarracks); },
		});

	// TODO: Define create sword task
	Task createSwordBlueprint = Task({
		[](Worker& worker, float dTime) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::BuildingSmithy);  },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::CreateSword(worker); },
		});

	// TODO: Define create soldier task
	Task recruitSoldierBlueprint = Task({
		[](Worker& worker, float dTime) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::BuildingSmithy);  },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::RecruitSoldier(worker); },
		});

	// Resources
	GatheredResources* resources;
};

// Commander
Commander::Commander(ComponentsManager* componentManager, EntityManager* entityManager)
{
	data = new Commander::Data{};
	this->entityManager = entityManager;

	data->resources = componentManager->gatheredResources;

	// Test command
	Task testTask = data->createSwordBlueprint;
	testTask.assignee = this->entityManager->workers[0];

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

	std::string strWood = "Wood: " + std::to_string(data->resources->wood);
	char const* txtWood = strWood.c_str();
	DrawText(txtWood, 50, yPos, 24, BLACK);

	std::string strCoal = "Coal: " + std::to_string(data->resources->coal);
	char const* txtCoal = strCoal.c_str();
	DrawText(txtCoal, 180, yPos, 24, BLACK);

	std::string strIron = "Iron: " + std::to_string(data->resources->iron);
	char const* txtIron = strIron.c_str();
	DrawText(txtIron, 300, yPos, 24, BLACK);

	std::string strSwords = "Swords: " + std::to_string(data->resources->swords);
	char const* txtSwords = strSwords.c_str();
	DrawText(txtSwords, 450, yPos, 24, BLACK);

	std::string stSoldiers = "Soldiers: " + std::to_string(data->resources->soldiers);
	char const* txtSoldiers = stSoldiers.c_str();
	DrawText(txtSoldiers, 600, yPos, 24, BLACK);
}