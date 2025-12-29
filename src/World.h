#include <raylib.h>

class ComponentsManager;

class World
{
public:
    int tileSize = 32;
    int worldSize, width, height;
    bool* discovered; // Blocks discovered by NCPs, Undicovered will be covered in fog

    Texture2D* fogTexture;

    World(int w, int h, ComponentsManager* cmpManager);

    void Draw();
};