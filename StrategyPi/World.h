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
    Sword,
    Soldier,
    BuildingStorage,
    BuildingSmithy,
    BuildingBarracks,
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
    int worldSize, width, height;

    // Map data
    int undiscoveredCount;
    bool* discovered; // Blocks discovered by NCPs, Undiscovered will be covered in fog
    MaterialResource** mapResources; // What NPCs can mine

    // Textures
    Texture2D* stoneTexture;
    Texture2D* fogTexture;
    Texture2D* treeTexture;
    Texture2D* coalTexture;
    Texture2D* ironTexture;
    Texture2D* storageTexture;
    Texture2D* smithyTexture;
    Texture2D* barracksTexture;

    EntityManager* entityManager;

    // Helper data
    bool hSmithyExists;
    bool hBarracksExists;

    World(const char* path, ComponentsManager* cmpManager, EntityManager* entManager);
    ~World();

    bool LoadMap(const char* path);
    void Update(float dTime);
    void Draw();

    void SetResource(int x, int y, EMaterialResourceType type, int amount);
};