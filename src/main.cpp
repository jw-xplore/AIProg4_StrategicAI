#include <raylib.h>
#include "EntityManager.h"
#include "ComponentsManager.h"
#include "Worker.h"

// Game vars
EntityManager* entityManager;
ComponentsManager* components;

int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    // Window setup
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    // Setup entities
    entityManager = new EntityManager();
    components = new ComponentsManager();

    //Worker* worker = new Worker(components->steeringBehavior);
    entityManager->AddEntities({
        new Worker(components->steeringBehavior),
        new Worker(components->steeringBehavior),
        new Worker(components->steeringBehavior),
        new Worker(components->steeringBehavior),
        new Worker(components->steeringBehavior)
    });
    
    // Gameloop
    while (!WindowShouldClose())
    {   
        // Update entities
        float dt = GetFrameTime();
        entityManager->UpdateEntities(dt);

        // Rendering
        BeginDrawing();
            ClearBackground(darkGreen);
            entityManager->DrawEntities();
        EndDrawing();
    }
    
    // End
    CloseWindow();
}