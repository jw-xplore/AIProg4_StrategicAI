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
#include "DecisionTree.h"
#include "CommanderDecisions.h"

//Commander data storage
struct Commander::Data
{
	// Worker tasks definitions
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

	Task createSwordBlueprint = Task({
		[](Worker& worker, float dTime) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::BuildingSmithy);  },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::CreateSword(worker); },
		});

	Task recruitSoldierBlueprint = Task({
		[](Worker& worker, float dTime) { return SubtaskDefinitions::FindNearestResource(worker, EMaterialResourceType::BuildingBarracks);  },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		[](Worker& worker, float dTime) { return SubtaskDefinitions::RecruitSoldier(worker); },
		});

	Task exploreBlueprint = Task({
		//[](Worker& worker, float dTime) { return SubtaskDefinitions::Discover(worker, dTime); },
		SubtaskDefinitions::Discover,
		[](Worker& worker, float dTime) { return SubtaskDefinitions::Arrive(worker); },
		});
		
	// Decisions
	DecisionTreeNode* soldierCreateTree;
	DecisionTreeNode* gatherResourceTree;
};

// Commander
Commander::Commander(ComponentsManager* componentManager, EntityManager* entityManager, World* world)
{
	data = new Commander::Data{};
	this->entityManager = entityManager;
	this->world = world;

	resources = componentManager->gatheredResources;
	goalDone = false;

	// Test command
	/*
	Task testTask = data->buildBarracksBlueprint;
	testTask.assignee = this->entityManager->workers[0];
	testTask.repeat = false;

	Task testTask2 = data->gatherWoodBlueprint;
	testTask2.assignee = this->entityManager->workers[1];
	testTask2.repeat = true;
	*/

	//activeTasks.push_back(testTask);
	//activeTasks.push_back(testTask2);

	// Test decision
	DefineDecisionTrees();

	Action* recruitAction = dynamic_cast<Action*>(data->soldierCreateTree->makeDecision());
	recruitAction->execute();
}

Commander::~Commander()
{
	activeTasks.clear();
	delete data->soldierCreateTree;
	delete data;
}

void Commander::Update(float dTime)
{
	// Goal fullfilled check
	if (resources->soldiers >= 20)
	{
		goalDone = true;
		return;
	}

	// Decision making

	// Tasks update
	for (size_t i = 0; i < activeTasks.size(); i++)
	{
		activeTasks[i].Update(dTime);
	}
}

void Commander::DrawUI()
{
	DrawRectangle(0, GlobalVars::SCREEN_HEIGHT - 100, GlobalVars::SCREEN_WIDTH, 100, GRAY);

	int yPos = GlobalVars::SCREEN_HEIGHT - 50;

	std::string strWood = "Wood: " + std::to_string(resources->wood);
	char const* txtWood = strWood.c_str();
	DrawText(txtWood, 50, yPos, 24, BLACK);

	std::string strCoal = "Coal: " + std::to_string(resources->coal);
	char const* txtCoal = strCoal.c_str();
	DrawText(txtCoal, 180, yPos, 24, BLACK);

	std::string strIron = "Iron: " + std::to_string(resources->iron);
	char const* txtIron = strIron.c_str();
	DrawText(txtIron, 300, yPos, 24, BLACK);

	std::string strSwords = "Swords: " + std::to_string(resources->swords);
	char const* txtSwords = strSwords.c_str();
	DrawText(txtSwords, 450, yPos, 24, BLACK);

	std::string stSoldiers = "Soldiers: " + std::to_string(resources->soldiers);
	char const* txtSoldiers = stSoldiers.c_str();
	DrawText(txtSoldiers, 600, yPos, 24, BLACK);
}

void Commander::AssignTask(Task& task)
{
	// Find free worker

	// Give task to worker
	Task testTask = task;
	testTask.assignee = this->entityManager->workers[0];
	testTask.repeat = false;

	activeTasks.push_back(testTask);
}

void Commander::DefineDecisionTrees()
{
	// Create soldier - main consideration
	data->soldierCreateTree = new CommanderDecisions::BuildingExists(this, EMaterialResourceType::BuildingBarracks);

	Decision* buildingDec = dynamic_cast<Decision*>(data->soldierCreateTree);
	buildingDec->positive = GatherResourcesTree(EMaterialResourceType::Soldier);

	Decision* resourceDec = dynamic_cast<Decision*>(buildingDec->positive);
	// Action* resourceDecEnd = dynamic_cast<Action*>(data->soldierCreateTree->makeDecision()); NOTE: Need to get ref to last decision
	resourceDec->positive = new CommanderDecisions::AssignTask(this, &data->recruitSoldierBlueprint);

	//buildingDec->positive = new CommanderDecisions::HasEnoughResources(this, EMaterialResourceType::BuildingBarracks, EMaterialResourceType::Wood); // Has enough wood?
	//buildingDec->positive = new CommanderDecisions::AssignTask(this, &data->recruitSoldierBlueprint);
	// buildingDec->negative =

	// Resources gathering
	//data->gatherResourceTree = new CommanderDecisions::HasEnoughResources(this, EMaterialResourceType::BuildingBarracks, EMaterialResourceType::Wood);
}

DecisionTreeNode* Commander::GatherResourcesTree(EMaterialResourceType goal)
{
	DecisionTreeNode* gatherTree = new CommanderDecisions::HasEnoughResources(this, goal, EMaterialResourceType::Wood);

	// Enought wood?
	Decision* woodDec = dynamic_cast<Decision*>(gatherTree);
	woodDec->positive = new CommanderDecisions::HasEnoughResources(this, goal, EMaterialResourceType::Iron);
	woodDec->negative = new CommanderDecisions::AssignTask(this, &data->gatherWoodBlueprint); // Gather wood

	// Enough iron?
	Decision* ironDec = dynamic_cast<Decision*>(woodDec->positive);
	ironDec->positive = new CommanderDecisions::HasEnoughResources(this, goal, EMaterialResourceType::Coal);
	ironDec->negative = new CommanderDecisions::AssignTask(this, &data->gatherIronBlueprint); // Gather iron

	// Enough coal?
	Decision* coalDec = dynamic_cast<Decision*>(ironDec->positive);
	coalDec->positive = new CommanderDecisions::HasEnoughResources(this, goal, EMaterialResourceType::Sword);
	coalDec->negative = new CommanderDecisions::AssignTask(this, &data->gatherCoalBlueprint); // Gather coal

	// Enough swords?
	Decision* swordDec = dynamic_cast<Decision*>(coalDec->positive);
	// Define positive response at outside
	swordDec->negative = new CommanderDecisions::AssignTask(this, &data->createSwordBlueprint); // Create sword

	return gatherTree;
}