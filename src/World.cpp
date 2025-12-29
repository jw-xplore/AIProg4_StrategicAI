#include "World.h"
#include "ComponentsManager.h"
#include "EntityManager.h"
#include "ImageLoader.h"
#include "Worker.h"
#include <raymath.h>

World::World(int w, int h, ComponentsManager* cmpManager, EntityManager* entManager)
{
    entityManager = entManager;

    // World setup
    worldSize = w * h;
    width = w;
    height = h;

    // Textures
    fogTexture = &cmpManager->imageLoader->textures[ELoadedImage::Fog];

    // Discovered parts
    discovered = new bool[worldSize];
    for (int i = 0; i < worldSize; i++)
    {
        discovered[i] = false;
    }
}

void World::Update(float dTime)
{
    // Discover world
    int i;
    int x, y;
    Vector2 pos;

    for (int i = 0; i < entityManager->workers.size(); i++)
    {
        pos = entityManager->workers[i]->position;
        pos.x = pos.x / tileSize;
        pos.y = pos.y / tileSize;

        i = (int)pos.y * width + (int)pos.x;
        discovered[i] = true;
    }
}

void World::Draw()
{
    int x, y;

    // Show fog 
    for (int i = 0; i < worldSize; i++)
    {
        if (discovered[i])
            continue;

        x = i % width;
        y = i / width;

        DrawTexture(*fogTexture, x * tileSize, y * tileSize, WHITE);
    }
}