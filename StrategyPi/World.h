#include <raylib.h>
#include <vector>

class ComponentsManager;
class EntityManager;

enum ETerrainType
{
    Grass,
    Swamp,
    Rock,
    Water,
    Trees,
    ETerrainTypeCount
};

/*
TODO: Remove this and split into meaningfull categories
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
    ETerrainType terrain;
    EMaterialResourceType type;
    int count;
};

struct Vector2Int
{
    int x, y;
};

struct TreesTile
{
    int x, y, amount;
    Vector2Int* treePositions;

    TreesTile(int tileX, int tileY, int count, int range)
    {
        x = tileX;
        y = tileY;
        amount = count;

        // Setup tree positions
        treePositions = new Vector2Int[count];

        for (size_t i = 0; i < count; i++)
        {
            treePositions[i].x = GetRandomValue(-range, range);
            treePositions[i].y = GetRandomValue(-range, range);
        }
    }

    ~TreesTile()
    {
        //delete[] treePositions;
    }
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
    MaterialResource** mapResources; // What NPCs can mine - TODO: Remove this as this structure is not helping for current implementation
    ETerrainType** mapTerrain;
    std::vector<TreesTile> treeTiles;

    // Textures
    Texture2D* stoneTexture;
    Texture2D* fogTexture;
    Texture2D* treeTexture;
    Texture2D* coalTexture;
    Texture2D* ironTexture;
    Texture2D* storageTexture;
    Texture2D* smithyTexture;
    Texture2D* barracksTexture;

    // Colors
    const Color cGrass = { 70, 100, 52, 255 };
    const Color cSwamp = { 37, 53, 18, 255 };
    const Color cRock = { 82, 87, 89, 255 };
    const Color cWater = { 56, 134, 219, 255 };

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