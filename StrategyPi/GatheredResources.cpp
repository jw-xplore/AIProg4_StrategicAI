#include "GatheredResources.h"
#include "World.h"

GatheredResources::GatheredResources()
{
	wood = 1000;
	coal = 0;
	iron = 0;
	swords = 0;
	soldiers = 0;

	// Define prices 
	prices = {
		{ EMaterialResourceType::BuildingSmithy, PlayerResources(100, 100, 50)},
		{ EMaterialResourceType::BuildingBarracks, PlayerResources(150, 20, 100)},
		{ EMaterialResourceType::Sword, PlayerResources(2, 10, 20, -1)},
		{ EMaterialResourceType::Soldier, PlayerResources(10, 0, 50, 1, -1)},
	};
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

bool GatheredResources::CanExchangeResource(EMaterialResourceType type)
{
	PlayerResources price = prices[type];

	if (wood - price.wood < 0)
		return false;

	if (coal - price.coal < 0)
		return false;

	if (iron - price.iron < 0)
		return false;

	if (swords - price.swords < 0)
		return false;

	if (soldiers - price.soldiers < 0)
		return false;

	return true;
}

bool GatheredResources::HasEnoughResourceType(EMaterialResourceType goal, EMaterialResourceType checkedType)
{
	PlayerResources price = prices[goal];

	switch (checkedType)
	{
	case EMaterialResourceType::Wood: return wood - price.wood > 0;
	case EMaterialResourceType::Coal: return coal - price.coal > 0;
	case EMaterialResourceType::Iron: return iron - price.iron > 0;
	case EMaterialResourceType::Sword: return swords - price.swords > 0;
	case EMaterialResourceType::Soldier: return soldiers - price.soldiers > 0;
	}

	return false;
}

bool GatheredResources::ExchangeToResource(EMaterialResourceType type)
{
	PlayerResources price = prices[type];

	// Check has enought resources
	if (wood - price.wood < 0)
		return false;

	if (coal - price.coal < 0)
		return false;

	if (iron - price.iron < 0)
		return false;

	if (swords - price.swords < 0)
		return false;

	if (soldiers - price.soldiers < 0)
		return false;

	// Calculate
	wood -= price.wood;
	coal -= price.coal;
	iron -= price.iron;
	swords -= price.swords;
	soldiers -= price.soldiers;

	return true;
}

/*
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
*/