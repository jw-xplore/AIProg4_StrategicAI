#include "ComponentsManager.h"
#include "SteeringBehavior.h"
#include "ImageLoader.h"
#include "PathFinding.h"
#include "World.h"
#include "GatheredResources.h"

ComponentsManager::ComponentsManager()
{
    steeringBehaviorData = new SteeringBehaviorData();
    imageLoader = new ImageLoader();
    gatheredResources = new GatheredResources();
}

ComponentsManager::~ComponentsManager()
{
    delete steeringBehaviorData;
    delete imageLoader;
    delete pathFinding;
    delete gatheredResources;
}

/*
Setup pathfinding
*/

void ComponentsManager::InitPathfinding(World* world)
{
    pathFinding = new PathFinding(world->width, world->height, world);
}