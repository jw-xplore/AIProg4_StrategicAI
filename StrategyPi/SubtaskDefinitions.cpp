#include "SubtaskDefinitions.h"
#include <raylib.h>
#include <raymath.h>
#include "World.h"
#include "Worker.h"
#include "Constants.h"
#include "SteeringBehavior.h"
#include "PathFinding.h"
#include "Commander.h"

bool SubtaskDefinitions::FindNearestResource(Worker& worker, EMaterialResourceType type)
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
		return false;
	}

	// Not found
	return true;
}

bool SubtaskDefinitions::MineAtPosition(Worker& worker, float dTime)
{
	return worker.MineAtPosition(dTime);
}

bool SubtaskDefinitions::Arrive(Worker& worker)
{
	if (!worker.path)
		return false;

	return !worker.path->empty();
}

/*
Choose random spot to create building - there should be nothing standing
*/
bool SubtaskDefinitions::PickBuildPosition(Worker& worker)
{
	int x = GetRandomValue(0, worker.world->width - 1);
	int y = GetRandomValue(0, worker.world->height - 1);

	// Position is occupied?
	if (worker.world->mapResources[y][x].type != EMaterialResourceType::None)
		return true;

	// Create path to position
	Vector2 pos = { x * GlobalVars::TILE_SIZE, y * GlobalVars::TILE_SIZE };
	worker.SetPath(worker.pathfinding->AStar(worker.position, pos));

	return false;
}