#include "ComponentsManager.h"
#include "SteeringBehavior.h"
#include "ImageLoader.h"
#include "PathFinding.h"
#include "World.h"

ComponentsManager::ComponentsManager()
{
    steeringBehavior = new SteeringBehavior();
    imageLoader = new ImageLoader();
}

ComponentsManager::~ComponentsManager()
{
    delete steeringBehavior;
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