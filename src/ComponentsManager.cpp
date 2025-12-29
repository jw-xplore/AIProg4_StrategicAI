#include "ComponentsManager.h"
#include "SteeringBehavior.h"
#include "ImageLoader.h"

ComponentsManager::ComponentsManager()
{
    steeringBehavior = new SteeringBehavior();
    imageLoader = new ImageLoader();
}

ComponentsManager::~ComponentsManager()
{
    delete steeringBehavior;
    delete imageLoader;
}