#include "ComponentsManager.h"
#include "SteeringBehavior.h"
#include "ImageLoader.h"
#include "PathFinding.h"
#include "World.h"

ComponentsManager::ComponentsManager()
{
    steeringBehaviorData = new SteeringBehaviorData();
    imageLoader = new ImageLoader();
}

ComponentsManager::~ComponentsManager()
{
    delete steeringBehaviorData;
    delete imageLoader;
    delete pathFinding;
}

/*
Setup pathfinding
*/

void ComponentsManager::InitPathfinding(World* world)
{
    pathFinding = new PathFinding(world->width, world->height, world);
}