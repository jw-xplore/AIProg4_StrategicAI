/*
Holds references to major game services used acrross the game
*/

class SteeringBehavior;

class ComponentsManager
{
public:
    SteeringBehavior* steeringBehavior;

    ComponentsManager();
    ~ComponentsManager();
};