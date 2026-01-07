#pragma once

class World;
class Commander;
class Worker;

enum EMaterialResourceType;

namespace SubtaskDefinitions
{
	bool FindNearestResource(Worker& worker, EMaterialResourceType type);
	bool MineAtPosition(Worker& worker);
	bool SubmitResource(Worker& worker, Commander* commander);

	bool Arrive(Worker& worker);
}