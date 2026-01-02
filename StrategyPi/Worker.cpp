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
    //target->position = GetMousePosition();
    //target->prevPosition = GetMousePosition();

    /*
    steering->linear = steeringBehavior->arrive(target, position, velocity, 20, 500, 32, 5);
    Vector2 separation = steeringBehavior->separate(this->steeringBehavior->separationObstacles, this, position, 20, 500);
    steering->linear.x += separation.x;
    steering->linear.y += separation.y;
    */

    if (path && !path->empty())
    {
        FollowPath();
    }
    else
    {
        steering->linear = { 0, 0 };
        velocity = { 0, 0 };
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
    if (currentPathNode < 0)
    {
        path->clear();
        currentPathNode = 0;
        return false;
    }

    // Follow next path point
    int x = (*path)[currentPathNode].x * GlobalVars::TILE_SIZE;
    int y = (*path)[currentPathNode].y * GlobalVars::TILE_SIZE;

    Vector2 pos = { x, y };
    Vector2 dist = pos - position;

    if (Vector2LengthSqr(dist) > pathNodeDistance)
    {
        // Follow next point until reached
        target->position = pos;

        //if (currentPathNode != 0)
            //steering->linear = steeringBehavior->seek(target, position, 50);
        //else
            steering->linear = steeringBehavior->arrive(target, position, velocity, 50, 500, 5, 5);

        Vector2 separation = steeringBehavior->separate(this->steeringBehavior->separationObstacles, this, position, 20, 500);
        steering->linear.x += separation.x;
        steering->linear.y += separation.y;

        DrawCircle(pos.x, pos.y, 10, RED);
    }
    else
    {
        // Progress to next
        currentPathNode--;
    }

    return true;
}

void Worker::SetPath(std::vector<Node>* newPath)
{
    path = newPath;
    currentPathNode = path->size() - 1;
}