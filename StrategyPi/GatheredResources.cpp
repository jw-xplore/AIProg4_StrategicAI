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

bool GatheredResources::AddSword()
{
	// Check materials
	if (iron < SWORD_IRON_COST)
		return false;

	if (coal < SWORD_COAL_COST)
		return false;

	// Exchange resources 
	iron -= SWORD_IRON_COST;
	coal -= SWORD_COAL_COST;
	swords++;

	return true;
}

bool GatheredResources::AddSoldier()
{
	// Check materials
	if (iron < SOLDIER_IRON_COST)
		return false;

	if (wood < SOLDIER_WOOD_COST)
		return false;

	if (swords < SOLDIER_SWORD_COST)
		return false;

	// Exchange resources 
	iron -= SOLDIER_IRON_COST;
	wood -= SOLDIER_WOOD_COST;
	swords -= SOLDIER_SWORD_COST;
	soldiers++;

	return true;
}