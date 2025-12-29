#include <raylib.h>
#include "EntityManager.h"
#include "ComponentsManager.h"
#include "World.h"
#include "Worker.h"

// Game vars
World* world;
ComponentsManager* components;
EntityManager* entityManager;

int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    // Window setup
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    // World and components
    components = new ComponentsManager();
    entityManager = new EntityManager();
    world = new World(8, 8, components, entityManager);
    
    // Setup entities
    //Worker* worker = new Worker(components->steeringBehavior);
    entityManager->AddWorkers({
        new Worker(components, world)
    });
    
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
        EndDrawing();
    }
    
    // End
    CloseWindow();
}