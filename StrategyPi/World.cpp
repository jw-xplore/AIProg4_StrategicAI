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
#include "Database.h"

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
    SetResource(9, 2, EMaterialResourceType::BuildingBarracks, 1);
}

World::~World()
{
    delete discovered;

    for (int y = 0; y < height; y++)
    {
        delete[] mapResources[y];
        delete[] mapTerrain[y];
    }

    delete[] mapResources;
    delete[] mapTerrain;
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
            if (this->width == 0)
			    this->width = line.size();
		}

        // Define resources
        worldSize = width * height;
        mapTerrain = new ETerrainType*[height];
        mapResources = new MaterialResource*[height]; // Safe keeping

        GameDB::Database* db = GameDB::Database::Instance();

        for (int y = 0; y < height; y++)
        {
            mapTerrain[y] = new ETerrainType[width];
            mapResources[y] = new MaterialResource[width]; // Safe keeping

            for (int x = 0; x < width; x++)
            {
                // Terrain types
                if (map[y][x] == db->terrains[ETerrainType::Grass].charIdentifier)
                    mapTerrain[y][x] = ETerrainType::Grass;

                if (map[y][x] == db->terrains[ETerrainType::Swamp].charIdentifier)
                    mapTerrain[y][x] = ETerrainType::Swamp;

                if (map[y][x] == db->terrains[ETerrainType::Water].charIdentifier)
                    mapTerrain[y][x] = ETerrainType::Water;

                if (map[y][x] == db->terrains[ETerrainType::Rock].charIdentifier)
                    mapTerrain[y][x] = ETerrainType::Rock;

                // Trees
                if (map[y][x] == db->terrains[ETerrainType::Trees].charIdentifier)
                {
                    mapTerrain[y][x] = ETerrainType::Grass;
                    treeTiles.push_back(TreesTile(x, y, 5, GlobalVars::TILE_HALF_SIZE));
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
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Show fog 
            /*
            if (!discovered[i])
            {
                DrawTexture(*fogTexture, x * GlobalVars::TILE_SIZE, y * GlobalVars::TILE_SIZE, WHITE);
                continue;
            }
            */

            // Show terrain
            Color col = cGrass;

            switch (mapTerrain[y][x])
            {
            case ETerrainType::Grass: col = cGrass; break;
            case ETerrainType::Swamp: col = cSwamp; break;
            case ETerrainType::Water: col = cWater; break;
            case ETerrainType::Rock: col = cRock; break;
            }

            DrawRectangle(x * GlobalVars::TILE_SIZE, y * GlobalVars::TILE_SIZE, GlobalVars::TILE_SIZE, GlobalVars::TILE_SIZE, col);
        }
    }

    // Show trees
    for (size_t i = 0; i < treeTiles.size(); i++)
    {
        for (size_t t = 0; t < treeTiles[i].amount; t++)
        {
            Vector2 pos = { 
                treeTiles[i].x * GlobalVars::TILE_SIZE + treeTiles[i].treePositions[t].x,
                treeTiles[i].y * GlobalVars::TILE_SIZE + treeTiles[i].treePositions[t].y 
            };

            DrawCircle(pos.x, pos.y, 2, BROWN);
        }
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