#include <raylib.h>
#include "EntityManager.h"
#include "ComponentsManager.h"
#include "World.h"
#include "Worker.h"
#include "PathFinding.h"

// Game vars
World* world;
ComponentsManager* components;
EntityManager* entityManager;

int main()
{
    const Color darkGreen = { 46, 112, 32, 255 };

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    // Window setup
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    // World and components
    components = new ComponentsManager();
    entityManager = new EntityManager();
    world = new World("resources/map.txt", components, entityManager);
    components->InitPathfinding(world);

    // Setup entities
    entityManager->workers.push_back(std::make_unique<Worker>(components, world));
    entityManager->workers.push_back(std::make_unique<Worker>(components, world));

    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    //_CrtDumpMemoryLeaks();

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