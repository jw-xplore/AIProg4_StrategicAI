#include "AllSubtasks.h"
#include <raylib.h>
#include <raymath.h>
#include "Constants.h"
#include "World.h"
#include "Worker.h"

/*
Find closest material resource in world map
*/
bool FindClosestResourceSubtaks::Execute(float dTime)
{
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
				float dist = Vector2DistanceSqr(worker->position, pos);

				if (closestDist > dist || closestDist == -1)
					closestDist = dist;
			}
		}
	}

	// Found - Task finished
	if (closestDist != -1)
		return false;

	// Not found
	return true;
}