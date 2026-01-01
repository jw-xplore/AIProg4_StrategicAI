#include <raylib.h>

class ComponentsManager;
class EntityManager;

/*
Material definition
*/
enum EMaterialResourceType
{
    None,
    Wall,
    Wood,
    Coal,
    Iron,
    EMaterialResourceTypeCount
};

struct MaterialResource
{
    EMaterialResourceType type;
    int count;
};

/*
World map
*/
class World
{
public:
    int tileSize = 32;
    int worldSize, width, height;

    // Map data
    bool* discovered; // Blocks discovered by NCPs, Undiscovered will be covered in fog
    MaterialResource* mapResources; // What NPCs can mine

    Texture2D* stoneTexture;
    Texture2D* fogTexture;
    Texture2D* treeTexture;
    Texture2D* coalTexture;
    Texture2D* ironTexture;

    EntityManager* entityManager;

    World(const char* path, ComponentsManager* cmpManager, EntityManager* entManager);
    ~World();

    bool LoadMap(const char* path);
    void Update(float dTime);
    void Draw();
};