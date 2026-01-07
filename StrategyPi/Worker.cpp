#include "Worker.h"
#include "ComponentsManager.h"
#include "World.h"
#include "SteeringBehavior.h"
#include "ImageLoader.h"
#include <iostream>
#include "PathFinding.h"
#include <raylib.h>
#include <raymath.h>
#include "Constants.h"
#include <string>
#include "GatheredResources.h"

Worker::Worker(ComponentsManager* componentsManager, World* world, Vector2 startPos)
{
    //steeringBehavior = componentsManager->steeringBehavior;
    //steeringBehavior->separationObstacles.push_back(this);
    gatheredResources = componentsManager->gatheredResources;

    this->world = world;
    steeringBehaviorData = componentsManager->steeringBehaviorData;
    pathfinding = componentsManager->pathFinding;

    steeringBehaviorData->separationObstacles.push_back(this);

    image = componentsManager->imageLoader->textures[ELoadedImage::Worker];

    target = new SteerTarget();
    position = startPos;

    pathNodeDistance = pathNodeDistance * pathNodeDistance; // Powering distance to be able use squared distance

    carriedMaterialType = EMaterialResourceType::None;
    carriedMaterialAmount = 0;
}

Worker::~Worker()
{
    if (path)
    {
        path->clear();
        delete path; // NOTE: This helps, because path is stored here, but it feels prone to issues
    }

    delete target;
}

void Worker::Update(float dTime)
{
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

    // Show carried material
    std::string s = std::to_string(carriedMaterialAmount);
    char const* txt = s.c_str();
    DrawText(txt, position.x, position.y, 16, BLACK);
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
    int x = (*path)[currentPathNode].x * GlobalVars::TILE_SIZE + GlobalVars::TILE_SIZE * 0.5f;
    int y = (*path)[currentPathNode].y * GlobalVars::TILE_SIZE + GlobalVars::TILE_SIZE * 0.5f;

    Vector2 pos = { x, y };
    Vector2 dist = pos - position;

    if (Vector2LengthSqr(dist) > pathNodeDistance)
    {
        // Follow next point until reached
        target->position = pos;

        //if (currentPathNode != 0)
            //steering->linear = steeringBehavior->seek(target, position, 50);
        //else
        //steering->linear = steeringBehavior->arrive(target, position, velocity, 50, 500, 5, 5);
        steering->linear = SteeringBehavior::arrive(target, position, velocity, 50, 500, 5, 5);

        Vector2 separation = SteeringBehavior::separate(steeringBehaviorData->separationObstacles, this, position, 20, 500);
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

// Gather resources at current position
bool Worker::MineAtPosition(float dTime)
{
    // Overloaded
    if (carriedMaterialAmount >= maxCarriedAmount)
        return false;

    // Check current position
    int x = position.x / GlobalVars::TILE_SIZE;
    int y = position.y / GlobalVars::TILE_SIZE;
    int currentPos = y * world->width + x;
    MaterialResource currentPosResource = world->mapResources[currentPos];

    if (currentPosResource.count <= 0)
        return false;

    if (carriedMaterialType == EMaterialResourceType::None || carriedMaterialType == currentPosResource.type)
    {
        // Mine
        mineTimer -= dTime;

        if (mineTimer <= 0)
        {
            // Gain resource and restart timer
            carriedMaterialAmount++;
            currentPosResource.count--;
            carriedMaterialType = currentPosResource.type;

            mineTimer = mineDelay;
        }

        return true;
    }

    return false;
}

// Submit material at storage
bool Worker::SubmitMaterial()
{
    if (carriedMaterialType == EMaterialResourceType::None)
        return false;

    // Check current position
    int x = position.x / GlobalVars::TILE_SIZE;
    int y = position.y / GlobalVars::TILE_SIZE;
    int currentPos = y * world->width + x;
    MaterialResource currentPosResource = world->mapResources[currentPos];

    if (currentPosResource.type == EMaterialResourceType::BuildingStorage)
    {
        // Submit carried material
        gatheredResources->AddResource(carriedMaterialType, carriedMaterialAmount);

        carriedMaterialType = EMaterialResourceType::None;
        carriedMaterialAmount = 0;

        return true;
    }

    return false;
}