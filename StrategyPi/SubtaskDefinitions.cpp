#include "SubtaskDefinitions.h"
#include <raylib.h>
#include <raymath.h>
#include "World.h"
#include "Worker.h"
#include "Constants.h"
#include "SteeringBehavior.h"
#include "PathFinding.h"
#include "Commander.h"
#include "Task.h"
#include "GatheredResources.h"

ESubtaskState SubtaskDefinitions::FindNearestResource(Worker& worker, EMaterialResourceType type)
{
	World* world = worker.world;
	float closestDist = -1;
	Vector2 closestPos;
	int i = 0;

	for (int y = 0; y < world->height; y++)
	{
		for (int x = 0; x < world->width; x++)
		{
			// Ignore hidden
			/*
			if (!world->discovered[i])
				continue;
			*/

			// Compare searched resource
			if (type == world->mapResources[y][x].type)
			{
				Vector2 pos = { x * GlobalVars::TILE_SIZE, y * GlobalVars::TILE_SIZE };
				float dist = Vector2DistanceSqr(worker.position, pos);

				if (closestDist > dist || closestDist == -1)
				{
					closestDist = dist;
					closestPos = pos;
				}
			}

			i++;
		}
	}

	// Found - Task finished
	if (closestDist != -1)
	{
		worker.SetPath(worker.pathfinding->AStar(worker.position, closestPos));
		return ESubtaskState::Finnished;
	}

	// Not found
	return ESubtaskState::Canceled;
}

ESubtaskState SubtaskDefinitions::MineAtPosition(Worker& worker, float dTime)
{
	// Overloaded - Finish to drop material
	if (worker.carriedMaterialAmount >= worker.maxCarriedAmount)
		return ESubtaskState::Finnished;

	// Check current position
	int x = worker.position.x / GlobalVars::TILE_SIZE;
	int y = worker.position.y / GlobalVars::TILE_SIZE;

	MaterialResource currentPosResource = worker.world->mapResources[y][x];

	if (currentPosResource.count <= 0)
		return ESubtaskState::Finnished;

	// Check if can mine more resource of carried type
	if (worker.carriedMaterialType != EMaterialResourceType::None && worker.carriedMaterialType != currentPosResource.type)
		return ESubtaskState::Finnished;

	// Mine
	worker.MineAtPosition(dTime);
	return ESubtaskState::Running;
}

ESubtaskState SubtaskDefinitions::Arrive(Worker& worker)
{
	if (!worker.path)
		return ESubtaskState::Canceled;

	// Finish on path being cleared
	if (worker.path->empty())
		return ESubtaskState::Finnished;

	// Continue following path
	return ESubtaskState::Running;
}

/*
Choose random spot to create building - there should be nothing standing
*/
ESubtaskState SubtaskDefinitions::PickBuildPosition(Worker& worker)
{
	int x = GetRandomValue(0, worker.world->width - 1);
	int y = GetRandomValue(0, worker.world->height - 1);

	// Position is occupied?
	if (worker.world->mapResources[y][x].type != EMaterialResourceType::None)
		return ESubtaskState::Running;

	// Create path to position
	Vector2 pos = { x * GlobalVars::TILE_SIZE, y * GlobalVars::TILE_SIZE };
	worker.SetPath(worker.pathfinding->AStar(worker.position, pos));

	return ESubtaskState::Finnished;
}

ESubtaskState SubtaskDefinitions::SubmitMaterial(Worker& worker, float dTime)
{
	if (worker.SubmitMaterial())
		return ESubtaskState::Finnished;

	ESubtaskState::Canceled;
}

ESubtaskState SubtaskDefinitions::CreateBuilding(Worker& worker, float dTime, EMaterialResourceType type)
{
	if (worker.CreateBuilding(type, dTime))
		return ESubtaskState::Finnished;

	ESubtaskState::Canceled;
}

/*
Add swords if at smithy and has resources
*/
ESubtaskState SubtaskDefinitions::CreateSword(Worker& worker)
{
	int x = worker.position.x / GlobalVars::TILE_SIZE;
	int y = worker.position.y / GlobalVars::TILE_SIZE;

	// Is at smithy?
	if (worker.world->mapResources[y][x].type != EMaterialResourceType::BuildingSmithy)
		return ESubtaskState::Canceled;

	// Create sword
	if (worker.gatheredResources->AddSword())
		return ESubtaskState::Finnished;

	return ESubtaskState::Canceled;
}

ESubtaskState SubtaskDefinitions::RecruitSoldier(Worker& worker)
{
	int x = worker.position.x / GlobalVars::TILE_SIZE;
	int y = worker.position.y / GlobalVars::TILE_SIZE;

	// Is at barracks?
	if (worker.world->mapResources[y][x].type != EMaterialResourceType::BuildingBarracks)
		return ESubtaskState::Canceled;

	// Recruit soldier
	if (worker.gatheredResources->AddSoldier())
		return ESubtaskState::Finnished;

	return ESubtaskState::Canceled;
}