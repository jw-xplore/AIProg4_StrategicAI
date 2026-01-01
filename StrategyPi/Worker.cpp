#include "Worker.h"
#include "ComponentsManager.h"
#include "World.h"
#include "SteeringBehavior.h"
#include "ImageLoader.h"
#include <iostream>

Worker::Worker(ComponentsManager* componentsManager, World* world)
{
    steeringBehavior = componentsManager->steeringBehavior;
    steeringBehavior->separationObstacles.push_back(this);

    image = componentsManager->imageLoader->textures[ELoadedImage::Worker];

    target = new SteerTarget();
    position = { 100, 100 };
}

Worker::~Worker()
{
    delete target;
}

void Worker::Update(float dTime)
{
    target->position = GetMousePosition();
    target->prevPosition = GetMousePosition();

    steering->linear = steeringBehavior->arrive(target, position, velocity, 20, 500, 32, 5);
    Vector2 separation = steeringBehavior->separate(this->steeringBehavior->separationObstacles, this, position, 20, 500);
    steering->linear.x += separation.x;
    steering->linear.y += separation.y;

    Entity::Update(dTime);
}

void Worker::Draw()
{
    DrawTexture(image, position.x - 16, position.y - 16, WHITE);
}