#include "Entity.h"

class SteeringBehavior;
class SteerTarget;

class Worker : public Entity
{
public:
    Texture2D image;
    SteeringBehavior* steeringBehavior;
    SteerTarget* target;

    Worker(SteeringBehavior* steeringBehavior);
    void Update(float dTime) override;
    void Draw() override;
};