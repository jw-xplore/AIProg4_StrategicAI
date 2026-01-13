#include "CommanderDecisions.h"
#include "World.h"
#include "Commander.h"
#include "GatheredResources.h";

using namespace CommanderDecisions;

//---------------------------------------------------------------
// Decisions
//---------------------------------------------------------------

bool BuildingExists::pass()
{
	// Smithy
	if (buildingType == EMaterialResourceType::BuildingSmithy && commander->world->hSmithyExists)
		return true;

	// Barracks
	if (buildingType == EMaterialResourceType::BuildingBarracks && commander->world->hBarracksExists)
		return true;

	return false;
}

// NOTE: This should be replaced with HasRequiredResources
bool HasEnoughResources::pass()
{
	return commander->resources->HasEnoughResourceType(goal, type);
}

//---------------------------------------------------------------
// Actions
//---------------------------------------------------------------

void AssignTask::execute()
{
	commander->AssignTask(*task);
}

//---------------------------------------------------------------
// Custom
//---------------------------------------------------------------

/// <summary>
/// Returns node releated to handeling a missing resource, otherwise return continue behavior node
/// Each node option should be related to gathering the given resource
/// </summary>
/// <returns></returns>
DecisionTreeNode* HasRequiredResources::makeDecision()
{
	GatheredResources* res = commander->resources;
	PlayerResources price = res->prices[goal];

	if (res->wood - price.wood < 0)
		return woodNode;

	if (res->coal - price.coal < 0)
		return coalNode;

	if (res->iron - price.iron < 0)
		return ironNode;

	if (res->swords - price.swords < 0)
		return swordsNode;

	return continueNode;
}
