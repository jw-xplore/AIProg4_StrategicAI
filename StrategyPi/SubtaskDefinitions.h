#pragma once

class World;
class Worker;

enum EMaterialResourceType;

namespace SubtaskDefinitions
{
	bool FindNearestResource(Worker& worker, EMaterialResourceType type);
	bool MineAtPosition(Worker& worker);

	bool Arrive(Worker& worker);
}