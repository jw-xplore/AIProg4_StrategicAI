#include "Worker.h"
#include "SteeringBehavior.h"
#include <iostream>

Worker::Worker(SteeringBehavior* steeringBehavior)
{
    this->steeringBehavior = steeringBehavior;
    this->steeringBehavior->separationObstacles.push_back(this);

    target = new SteerTarget();
    position = { 100, 100 };
    image = LoadTexture("resources/npc_worker.png");
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
    //std::cout << "steerOutput: " << steerOutput.x << std::endl;
}

void Worker::Draw()
{
    DrawTexture(image, position.x, position.y, WHITE);
}