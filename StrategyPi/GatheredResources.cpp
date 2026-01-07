#include "GatheredResources.h"
#include "World.h"

GatheredResources::GatheredResources()
{
	wood = 1;
	coal = 2;
	iron = 3;
	swords = 4;
	soldiers = 5;
}

void GatheredResources::AddResource(EMaterialResourceType type, int amount)
{
	switch (type)
	{
	case EMaterialResourceType::Wood: wood += amount; break;
	case EMaterialResourceType::Coal: coal += amount; break;
	case EMaterialResourceType::Iron: iron += amount; break;
	case EMaterialResourceType::Sword: swords += amount; break;
	case EMaterialResourceType::Soldier: soldiers += amount; break;
	}
}