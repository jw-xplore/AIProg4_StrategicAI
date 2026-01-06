#include "Entity.h"
#include <vector>

class ComponentsManager;
class World;
class SteeringBehaviorData;
class SteerTarget;
class ImageLoader;
class PathFinding;
struct Node;
struct MaterialResource;
enum EMaterialResourceType;

class Worker : public Entity
{
public:
    // Refs
    World* world;
    SteeringBehaviorData* steeringBehaviorData;
    SteerTarget* target;
    
    // Path
    PathFinding* pathfinding;
    std::vector<Node>* path;
    int currentPathNode = 0;
    float pathNodeDistance = 10;

    Texture2D image;

    EMaterialResourceType carriedMaterialType;
    int carriedMaterialAmount;
    int maxCarriedAmount = 20;
    float mineDelay = 0.2f;
    float mineTimer = 0; 

    Worker(ComponentsManager* componentsManager, World* world, Vector2 startPos);
    ~Worker();

    void Update(float dTime) override;
    void Draw() override;

    bool FollowPath();
    void SetPath(std::vector<Node>* newPath);
    bool MineAtPosition(float dTime);
};