#include "World.h"
#include "ComponentsManager.h"
#include "EntityManager.h"
#include "ImageLoader.h"
#include "Worker.h"
#include <raymath.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Constants.h"

World::World(const char* path, ComponentsManager* cmpManager, EntityManager* entManager)
{
    entityManager = entManager;

    // World setup
    LoadMap(path);

    // Textures
    stoneTexture = &cmpManager->imageLoader->textures[ELoadedImage::Stone];
    fogTexture = &cmpManager->imageLoader->textures[ELoadedImage::Fog];
    treeTexture = &cmpManager->imageLoader->textures[ELoadedImage::Tree];
    coalTexture = &cmpManager->imageLoader->textures[ELoadedImage::CoalMine];
    ironTexture = &cmpManager->imageLoader->textures[ELoadedImage::IronMine];
    storageTexture = &cmpManager->imageLoader->textures[ELoadedImage::Storage];
    smithyTexture = &cmpManager->imageLoader->textures[ELoadedImage::Smithy];
    barracksTexture = &cmpManager->imageLoader->textures[ELoadedImage::Barracks];

    // Discovered parts
    discovered = new bool[worldSize];
    undiscoveredCount = worldSize;

    for (int i = 0; i < worldSize; i++)
    {
        discovered[i] = false;
    }

    // Add testing buildings
    SetResource(8, 2, EMaterialResourceType::BuildingSmithy, 1);
    //SetResource(9, 2, EMaterialResourceType::BuildingBarracks, 1);
}

World::~World()
{
    delete discovered;

    for (int y = 0; y < height; y++)
    {
        delete[] mapResources[y];
    }

    delete[] mapResources;
}

void World::Update(float dTime)
{
    // Discover world
    Vector2 pos;

    for (int i = 0; i < entityManager->workers.size(); i++)
    {
        pos = entityManager->workers[i]->position;
        pos.x = pos.x / GlobalVars::TILE_SIZE;
        pos.y = pos.y / GlobalVars::TILE_SIZE;

        i = (int)pos.y * width + (int)pos.x;

        // Discover
        if (!discovered[i])
            undiscoveredCount--;

        discovered[i] = true;
    }
}

/*
Load map data and create world setup
*/
bool World::LoadMap(const char* path)
{
    // Load file
	std::ifstream file;
	file.open(path);

	// Define array
	int lines = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
	height = lines + 1;

    const char** map = new const char*[height];

	// Restart line reading
	int currentLine = 0;
	file.clear();
	file.seekg(0);

	// Read file
	if (file.is_open())
	{
		std::string line;

        // Read all the lines
		while (std::getline(file, line))
		{
			char* cstr = new char[line.size()];
			for (size_t i = 0; i < line.size(); ++i)
			{
				cstr[i] = line[i];
			}

		    map[currentLine] = cstr;

			currentLine++;
			this->width = line.size();
		}

        // Define resources
        worldSize = width * height;
        mapResources = new MaterialResource*[height];

        for (int y = 0; y < height; y++)
        {
            mapResources[y] = new MaterialResource[width];

            for (int x = 0; x < width; x++)
            {
                switch (map[y][x])
                {
                case 'T': mapResources[y][x].type = EMaterialResourceType::Wood; mapResources[y][x].count = 50; break;
                case 'C': mapResources[y][x].type = EMaterialResourceType::Coal; mapResources[y][x].count = 1000; break;
                case 'I': mapResources[y][x].type = EMaterialResourceType::Iron; mapResources[y][x].count = 1000; break;
                case 'X': mapResources[y][x].type = EMaterialResourceType::Wall; mapResources[y][x].count = 1; break;
                case 'S': mapResources[y][x].type = EMaterialResourceType::BuildingStorage; mapResources[y][x].count = 1; break;
                default: mapResources[y][x].type = EMaterialResourceType::None; break;
                }
            }
        }

        // Clearup
        for (int y = 0; y < height; y++)
        {
            delete[] map[y];
        }

        delete[] map;

        // Stop reading
		file.close();
		return true;
	}

	// Fail to read
	return false;
}

void World::Draw()
{
    int x, y;

    for (int i = 0; i < worldSize; i++)
    {
        x = i % width;
        y = i / width;

        // Show fog 
        if (!discovered[i])
        {
            //DrawTexture(*fogTexture, x * GlobalVars::TILE_SIZE, y * GlobalVars::TILE_SIZE, WHITE);
            //continue;
        }

        // Show resources
        if (mapResources[y][x].count <= 0)
            continue;

        Texture2D texture;

        switch (mapResources[y][x].type)
        {
            case EMaterialResourceType::Wood: texture = *treeTexture; break;
            case EMaterialResourceType::Coal: texture = *coalTexture; break;
            case EMaterialResourceType::Iron: texture = *ironTexture; break;
            case EMaterialResourceType::Wall: texture = *stoneTexture; break;
            case EMaterialResourceType::BuildingStorage: texture = *storageTexture; break;
            case EMaterialResourceType::BuildingSmithy: texture = *smithyTexture; break;
            case EMaterialResourceType::BuildingBarracks: texture = *barracksTexture; break;
        }

        DrawTexture(texture, x * GlobalVars::TILE_SIZE, y * GlobalVars::TILE_SIZE, WHITE);
    }
}

void World::SetResource(int x, int y, EMaterialResourceType type, int amount)
{
    mapResources[y][x].type = type;
    mapResources[y][x].count = amount;

    if (amount <= 0)
    {
        mapResources[y][x].type = EMaterialResourceType::None;
    }

    // Cache helpers
    if (amount < 1)
        return;

    if (type == EMaterialResourceType::BuildingSmithy)
        hSmithyExists = true;

    if (type == EMaterialResourceType::BuildingBarracks)
        hBarracksExists = true;
}