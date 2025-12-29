/*
Holds references to major game services used acrross the game
*/

class SteeringBehavior;
class ImageLoader;

class ComponentsManager
{
public:
    SteeringBehavior* steeringBehavior;
    ImageLoader* imageLoader;

    ComponentsManager();
    ~ComponentsManager();
};