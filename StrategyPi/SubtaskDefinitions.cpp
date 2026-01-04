#include "SubtaskDefinitions.h"
#include <raylib.h>
#include <raymath.h>
#include "World.h"
#include "Worker.h"
#include "Constants.h"
#include "SteeringBehavior.h"

bool SubtaskDefinitions::FindNearestResource(Worker& worker, EMaterialResourceType type)
{
	World* world = worker.world;
	float closestDist = -1;
	int i = 0;

	for (int y = 0; y < world->height; y++)
	{
		for (int x = 0; x < world->width; x++)
		{
			// Ignore hidden
			if (!world->discovered[i])
				continue;

			// Compare searched resource
			if (type == world->mapResources[i].type)
			{
				Vector2 pos = { x * GlobalVars::TILE_SIZE, y * GlobalVars::TILE_SIZE };
				float dist = Vector2DistanceSqr(worker.position, pos);

				if (closestDist > dist || closestDist == -1)
					closestDist = dist;
			}
		}
	}

	// Found - Task finished
	if (closestDist != -1)
	{
		//worker.path = 
		return false;
	}

	// Not found
	return true;
}

bool SubtaskDefinitions::FindNearestWood(Worker& worker)
{
	return FindNearestResource(worker, EMaterialResourceType::Wood);
}

bool SubtaskDefinitions::Arrive(Worker& worker)
{
	return worker.path->empty();
}