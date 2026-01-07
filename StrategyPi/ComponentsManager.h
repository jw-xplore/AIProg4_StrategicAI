/*
Holds references to major game services used acrross the game
*/

class SteeringBehaviorData;
class ImageLoader;
class PathFinding;
class World;
class GatheredResources;

class ComponentsManager
{
public:
    SteeringBehaviorData* steeringBehaviorData;
    ImageLoader* imageLoader;
    PathFinding* pathFinding;
    GatheredResources* gatheredResources;

    ComponentsManager();
    ~ComponentsManager();

    void InitPathfinding(World* world);
};