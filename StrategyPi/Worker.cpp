#include "Worker.h"
#include "ComponentsManager.h"
#include "World.h"
#include "SteeringBehavior.h"
#include "ImageLoader.h"
#include <iostream>
#include "PathFinding.h"
#include <raymath.h>
#include "Constants.h"

Worker::Worker(ComponentsManager* componentsManager, World* world)
{
    steeringBehavior = componentsManager->steeringBehavior;
    steeringBehavior->separationObstacles.push_back(this);

    image = componentsManager->imageLoader->textures[ELoadedImage::Worker];

    target = new SteerTarget();
    position = { 100, 100 };

    pathNodeDistance = pathNodeDistance * pathNodeDistance; // Powering distance to be able use squared distance
}

Worker::~Worker()
{
    delete target;
}

void Worker::Update(float dTime)
{
    target->position = GetMousePosition();
    target->prevPosition = GetMousePosition();

    /*
    steering->linear = steeringBehavior->arrive(target, position, velocity, 20, 500, 32, 5);
    Vector2 separation = steeringBehavior->separate(this->steeringBehavior->separationObstacles, this, position, 20, 500);
    steering->linear.x += separation.x;
    steering->linear.y += separation.y;
    */

    if (!path.empty())
    {
        FollowPath();
    }

    Entity::Update(dTime);
}

void Worker::Draw()
{
    DrawTexture(image, position.x - 16, position.y - 16, WHITE);
}

bool Worker::FollowPath()
{
    // Path finished? 
    if (currentPathNode >= path.size() - 1)
    {
        path.clear();
        currentPathNode = 0;
        return false;
    }

    // Follow next path point
    Vector2 pos = { path[currentPathNode]->x * GlobalVars::TILE_SIZE, path[currentPathNode]->y * GlobalVars::TILE_SIZE };
    Vector2 dist = pos - position;

    if (Vector2LengthSqr(dist) > pathNodeDistance)
    {
        // Follow next point until reached
        steering->linear = steeringBehavior->arrive(target, position, velocity, 20, 500, 32, 5);
        Vector2 separation = steeringBehavior->separate(this->steeringBehavior->separationObstacles, this, position, 20, 500);
        steering->linear.x += separation.x;
        steering->linear.y += separation.y;
    }

    return true;
}

void Worker::SetPath(std::vector<Node*> newPath)
{
    path = newPath;
    currentPathNode = 0;
}