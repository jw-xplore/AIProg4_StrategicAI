/*
Holds references to major game services used acrross the game
*/

class SteeringBehaviorData;
class ImageLoader;
class PathFinding;
class World;

class ComponentsManager
{
public:
    SteeringBehaviorData* steeringBehaviorData;
    ImageLoader* imageLoader;
    PathFinding* pathFinding;

    ComponentsManager();
    ~ComponentsManager();

    void InitPathfinding(World* world);
};