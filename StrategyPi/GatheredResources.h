#pragma once

enum EMaterialResourceType;

class GatheredResources
{
public: 
	int wood;
	int coal;
	int iron;
	int swords;
	int soldiers;

	GatheredResources();
	
	void AddResource(EMaterialResourceType type, int amount);
};

