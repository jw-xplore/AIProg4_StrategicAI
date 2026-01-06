#include "Entity.h"
#include <vector>

class ComponentsManager;
class World;
class SteeringBehaviorData;
class SteerTarget;
class ImageLoader;
class PathFinding;
struct Node;

class Worker : public Entity
{
public:
    World* world;
    SteeringBehaviorData* steeringBehaviorData;
    SteerTarget* target;
    
    PathFinding* pathfinding;
    std::vector<Node>* path;
    int currentPathNode = 0;
    float pathNodeDistance = 10;

    Texture2D image;

    Worker(ComponentsManager* componentsManager, World* world);
    ~Worker();

    void Update(float dTime) override;
    void Draw() override;

    bool FollowPath();
    void SetPath(std::vector<Node>* newPath);
};