#pragma once

class World;
class Commander;
class Worker;

enum EMaterialResourceType;

namespace SubtaskDefinitions
{
	bool FindNearestResource(Worker& worker, EMaterialResourceType type);
	bool MineAtPosition(Worker& worker, float dTime);

	bool Arrive(Worker& worker);

	bool PickBuildPosition(Worker& worker);
}