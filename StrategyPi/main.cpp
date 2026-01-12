#include <raylib.h>
#include "EntityManager.h"
#include "ComponentsManager.h"
#include "World.h"
#include "Worker.h"
#include "PathFinding.h"
#include "Constants.h"
#include "SteeringBehavior.h"
#include "Commander.h"
#include <string>

// Game vars
extern float TIME_SCALE = 1;

World* world;
ComponentsManager* components;
EntityManager* entityManager;
Commander* commander;

/*
Debug
*/
void DrawPath(std::vector<Node>* path)
{
    int halfSize = GlobalVars::TILE_SIZE / 2;

    for (int i = 0; i < path->size(); i++)
    {
        DrawCircle((*path)[i].x * GlobalVars::TILE_SIZE, (*path)[i].y * GlobalVars::TILE_SIZE, 8, BLUE);
    }
}

void AdjustTimeScale()
{
    if (IsKeyDown(KEY_RIGHT))
        TIME_SCALE += 0.1f;
    else  if (IsKeyDown(KEY_LEFT) && TIME_SCALE > 0.1)
        TIME_SCALE -= 0.1f;

    // Show time
    std::string strTime = "Time scale: " + std::to_string(TIME_SCALE);
    char const* cTime = strTime.c_str();
    DrawText(cTime, 50, 20, 24, YELLOW);
}

// Game functionality
int main()
{
    const Color darkGreen = { 46, 112, 32, 255 };

    constexpr int screenWidth = GlobalVars::SCREEN_WIDTH;
    constexpr int screenHeight = GlobalVars::SCREEN_HEIGHT;

    // Window setup
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    // World and components
    components = new ComponentsManager();
    entityManager = new EntityManager();
    world = new World("resources/map.txt", components, entityManager);
    components->InitPathfinding(world);
  

    // Setup entities
    entityManager->workers.push_back(new Worker(components, world, { 100, 100}));
    entityManager->workers.push_back(new Worker(components, world, { 200, 300 }));
    //entityManager->workers.push_back(std::make_shared<Worker>(components, world));
    //entityManager->workers.push_back(std::make_shared<Worker>(components, world));

    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    //_CrtDumpMemoryLeaks();

    // Debug find path - This testing causes leaks, it will be fixed with proper commander management
    //components->pathFinding->AStar({ 100, 100 }, { 400, 128 });
    //std::vector<Node>* path = components->pathFinding->AStar({ 100, 100 }, { 400, 128 });
    //entityManager->workers[0]->SetPath(path);
    //entityManager->workers[1]->SetPath(path);

    commander = new Commander(components, entityManager, world);

    // Gameloop
    while (!WindowShouldClose())
    {
        // Update entities
        float dt = GetFrameTime() * TIME_SCALE;
        entityManager->UpdateEntities(dt);
        world->Update(dt);
        commander->Update(dt);

        // Rendering
        BeginDrawing();
        ClearBackground(darkGreen);
        world->Draw();
        entityManager->DrawEntities();
        commander->DrawUI();

        //components->pathFinding->DrawGraph();
        //DrawPath(path);

        AdjustTimeScale();

        EndDrawing();
    }

    // End
    CloseWindow();

    // Cleanup
    delete commander;
    delete world;
    delete entityManager;
    delete components;

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
}