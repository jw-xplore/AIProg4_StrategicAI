#pragma once
#include <map>

enum EMaterialResourceType;

struct PlayerResources
{
	int wood;
	int coal;
	int iron;
	int swords;
	int soldiers;

	PlayerResources(int wo = 0, int co = 0, int ir = 0, int sw = 0, int so = 0) :
		wood{ wo }, coal{ co }, iron{ ir }, swords{ sw }, soldiers{ so }
	{
	}
};

class GatheredResources
{
public: 
	// Definies prices of good and buildings
	std::map<EMaterialResourceType, PlayerResources> prices;

	int wood;
	int coal;
	int iron;
	int swords;
	int soldiers;

	GatheredResources();
	
	void AddResource(EMaterialResourceType type, int amount);
	bool CanExchangeResource(EMaterialResourceType type); // Returns if all resources are in right amount
	bool HasEnoughResourceType(EMaterialResourceType goal, EMaterialResourceType checkedType); // Check if there is enough of one specific resource
	bool ExchangeToResource(EMaterialResourceType type);
};

