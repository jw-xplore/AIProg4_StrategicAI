/*
Holds references to major game services used acrross the game
*/

class SteeringBehavior;
class ImageLoader;
class PathFinding;
class World;

class ComponentsManager
{
public:
    SteeringBehavior* steeringBehavior;
    ImageLoader* imageLoader;
    PathFinding* pathFinding;

    ComponentsManager();
    ~ComponentsManager();

    void InitPathfinding(World* world);
};