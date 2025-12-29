#include <raylib.h>

class ComponentsManager;
class EntityManager;

class World
{
public:
    int tileSize = 32;
    int worldSize, width, height;
    bool* discovered; // Blocks discovered by NCPs, Undiscovered will be covered in fog

    Texture2D* fogTexture;

    EntityManager* entityManager;

    World(int w, int h, ComponentsManager* cmpManager, EntityManager* entManager);

    void Update(float dTime);
    void Draw();
};