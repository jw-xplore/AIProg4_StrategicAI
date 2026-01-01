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

World::World(const char* path, ComponentsManager* cmpManager, EntityManager* entManager)
{
    entityManager = entManager;

    // World setup
    LoadMap(path);
    //width = w;
    //height = h;

    // Textures
    fogTexture = &cmpManager->imageLoader->textures[ELoadedImage::Fog];
    treeTexture = &cmpManager->imageLoader->textures[ELoadedImage::Tree];
    coalTexture = &cmpManager->imageLoader->textures[ELoadedImage::CoalMine];
    ironTexture = &cmpManager->imageLoader->textures[ELoadedImage::IronMine];

    // Discovered parts
    discovered = new bool[worldSize];
    for (int i = 0; i < worldSize; i++)
    {
        discovered[i] = false;
    }
}

World::~World()
{
    delete discovered;
    delete mapResources;
}

void World::Update(float dTime)
{
    // Discover world
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
        mapResources = new MaterialResource[worldSize];

        int i = 0;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                switch (map[y][x])
                {
                case 'T': mapResources[i].type = EMaterialResourceType::Wood; mapResources[i].count = 50; break;
                case 'C': mapResources[i].type = EMaterialResourceType::Coal; mapResources[i].count = 1000; break;
                case 'I': mapResources[i].type = EMaterialResourceType::Iron; mapResources[i].count = 1000; break;
                default: mapResources[i].type = EMaterialResourceType::None; break;
                }
                
                i++;
            }
        }

        for (int y = 0; y < height; y++)
        {
            delete[] map[y];
        }

        delete[] map;

        // Stop reading
		file.close();
        //delete map;
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
            //DrawTexture(*fogTexture, x * tileSize, y * tileSize, WHITE);
            //continue;
        }

        // Show resources
        if (mapResources[i].count <= 0)
            continue;

        Texture2D texture;

        switch (mapResources[i].type)
        {
            case EMaterialResourceType::Wood: texture = *treeTexture; break;
            case EMaterialResourceType::Coal: texture = *coalTexture; break;
            case EMaterialResourceType::Iron: texture = *ironTexture; break;
        }

        DrawTexture(texture, x * tileSize, y * tileSize, WHITE);
    }
}