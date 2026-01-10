#pragma once

enum ESubtaskState;

class World;
class Commander;
class Worker;

enum EMaterialResourceType;

namespace SubtaskDefinitions
{
	ESubtaskState FindNearestResource(Worker& worker, EMaterialResourceType type);
	ESubtaskState MineAtPosition(Worker& worker, float dTime);

	ESubtaskState Arrive(Worker& worker);
	ESubtaskState Discover(Worker& worker, float dTime);

	ESubtaskState PickBuildPosition(Worker& worker);

	ESubtaskState SubmitMaterial(Worker& worker, float dTime);
	ESubtaskState CreateBuilding(Worker& worker, float dTime, EMaterialResourceType type);
	ESubtaskState CreateSword(Worker& worker);
	ESubtaskState RecruitSoldier(Worker& worker);
}