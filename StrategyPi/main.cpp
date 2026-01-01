#include <raylib.h>
#include "EntityManager.h"
#include "ComponentsManager.h"
#include "World.h"
#include "Worker.h"
#include "PathFinding.h"
#include "Constants.h"

// Game vars
World* world;
ComponentsManager* components;
EntityManager* entityManager;

void DrawPath(std::vector<Node*> path)
{
    int halfSize = GlobalVars::TILE_SIZE / 2;

    for (int i = 0; i < path.size(); i++)
    {
        DrawCircle(path[i]->x * GlobalVars::TILE_SIZE + halfSize, path[i]->y * GlobalVars::TILE_SIZE + halfSize, 8, BLUE);
    }
}

int main()
{
    const Color darkGreen = { 46, 112, 32, 255 };

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    // Window setup
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(5);

    // World and components
    components = new ComponentsManager();
    entityManager = new EntityManager();
    world = new World("resources/map.txt", components, entityManager);
    components->InitPathfinding(world);

    // Setup entities
    entityManager->workers.push_back(std::make_unique<Worker>(components, world));

    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    //_CrtDumpMemoryLeaks();

    // Debug find path
    std::vector<Node*> path = components->pathFinding->AStar({ 100, 100 }, { 400, 128 });

    // Gameloop
    while (!WindowShouldClose())
    {
        // Update entities
        float dt = GetFrameTime();
        entityManager->UpdateEntities(dt);
        world->Update(dt);

        // Rendering
        BeginDrawing();
        ClearBackground(darkGreen);
        world->Draw();
        entityManager->DrawEntities();

        components->pathFinding->DrawGraph();
        DrawPath(path);

        EndDrawing();
    }

    // End
    CloseWindow();
    
    delete world;
    delete entityManager;
    delete components;

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
}