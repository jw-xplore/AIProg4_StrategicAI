#include "ComponentsManager.h"
#include "SteeringBehavior.h"

ComponentsManager::ComponentsManager()
{
    steeringBehavior = new SteeringBehavior();
}

ComponentsManager::~ComponentsManager()
{
    delete steeringBehavior;
}