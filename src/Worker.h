#include "Entity.h"

class ComponentsManager;
class SteeringBehavior;
class SteerTarget;
class ImageLoader;

class Worker : public Entity
{
public:
    SteeringBehavior* steeringBehavior;
    SteerTarget* target;

    Texture2D image;

    Worker(ComponentsManager* componentsManager);
    void Update(float dTime) override;
    void Draw() override;
};