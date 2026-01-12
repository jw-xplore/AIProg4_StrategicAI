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