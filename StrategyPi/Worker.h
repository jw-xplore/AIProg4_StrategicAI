#include "Entity.h"
#include <vector>

class ComponentsManager;
class World;
class SteeringBehavior;
class SteerTarget;
class ImageLoader;
struct Node;

class Worker : public Entity
{
public:
    SteeringBehavior* steeringBehavior;
    SteerTarget* target;
    
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