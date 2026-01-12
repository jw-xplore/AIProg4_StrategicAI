#pragma once
#include <vector>

class EntityManager;
class Worker;

class World;
class Task;
class Subtask;
class ComponentsManager;
class DecisionTreeNode;
class GatheredResources;

enum EMaterialResourceType;

/*
Assigns tasks to NPCs and manages their resources like path
*/
class Commander
{
public:
	// Data storage
	struct Data;
	Data* data;

	World* world;
	EntityManager* entityManager;
	GatheredResources* resources;

	std::vector<Task> activeTasks;

	// Decision trees
	bool goalDone;

	Commander(ComponentsManager* componentManager, EntityManager* entityManager, World* world);
	~Commander();

	void Update(float dTime);
	void DrawUI();

	void DefineDecisionTrees();
	DecisionTreeNode* GatherResourcesTree(EMaterialResourceType goal, DecisionTreeNode*& connection);
	void AssignTask(Task& task);
};

