#pragma once

enum EMaterialResourceType;

class GatheredResources
{
public: 
	const int SWORD_COAL_COST = 5;
	const int SWORD_IRON_COST = 3;
	const int SOLDIER_SWORD_COST = 1;
	const int SOLDIER_IRON_COST = 2;
	const int SOLDIER_WOOD_COST = 3;

	int wood;
	int coal;
	int iron;
	int swords;
	int soldiers;

	GatheredResources();
	
	void AddResource(EMaterialResourceType type, int amount);
	bool AddSword();
	bool AddSoldier();
};

