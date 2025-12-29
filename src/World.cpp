#include "World.h"
#include "ComponentsManager.h"
#include "ImageLoader.h"

World::World(int w, int h, ComponentsManager* cmpManager)
{
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

void World::Draw()
{
    int x, y;

    // Show fog 
    for (int i = 0; i < worldSize; i++)
    {
        x = i % width;
        y = i / width;

        DrawTexture(*fogTexture, x * tileSize, y * tileSize, WHITE);
    }
}